#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <iostream>

#include "../include/protocol.hpp"
#include "../lib/networkOrder.hpp"
#include "program_options.hpp"

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <csignal>
#include <math.h>
#include <string.h>
#include <arpa/inet.h>  //ntoh

#include <chrono>

struct Parameter {
  std::string devicename;
  unsigned baud_rate;
};

int serial_fd_ = -1;

bool open_serial_port(const std::string& devicename) {
    if ((serial_fd_ = ::open(devicename.c_str(), O_RDWR | O_NOCTTY)) < 0) {
        std::cerr << "Cannot open serial device " << devicename << std::endl;
        return false;
    }
    return true;
}

void set_serial_properties(unsigned baud_rate) {
    tcflush(serial_fd_, TCIOFLUSH); // flush previous bytes

    struct termios tio;
    if(tcgetattr(serial_fd_, &tio) < 0)
        perror("tcgetattr");

    tio.c_iflag &= ~(INLCR | IGNCR | ICRNL | IXON | IXOFF);
    tio.c_oflag &= ~(ONLCR | OCRNL);
    tio.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);

    switch (baud_rate)
    {
    case 9600:   cfsetospeed(&tio, B9600);   break;
    case 19200:  cfsetospeed(&tio, B19200);  break;
    case 38400:  cfsetospeed(&tio, B38400);  break;
    case 115200: cfsetospeed(&tio, B115200); break;
    case 230400: cfsetospeed(&tio, B230400); break;
    case 460800: cfsetospeed(&tio, B460800); break;
    case 500000: cfsetospeed(&tio, B500000); break;
    default:
        printf("Baudrate of %d not supported, using 115200!\n", baud_rate);
        cfsetospeed(&tio, B115200);
        break;
    }
    cfsetispeed(&tio, cfgetospeed(&tio));

    if(tcsetattr(serial_fd_, TCSANOW, &tio) < 0) {
        printf("Could not set terminal attributes!\n");
        perror("tcsetattr");
    }
}

void send_command(const Command& cmd)
{
    const auto serialized =  cmd.message.getSerialized();
    const auto serializedNO = swapIfNotNetworkOrder(serialized);

    if(::write(serial_fd_, &cmd, sizeof(decltype(serializedNO))) < 0){
        printf("could not write Command %08lX\n", serializedNO);
        return;
    }
    printf("Probably successfully sent command %08lX\n", serializedNO);
}


int main(int argc, char* argv[])
{
    Parameter params;
    params.devicename = "/dev/ttyTapeDeck";
    params.baud_rate = 115200;

    const auto parameterList = po::fromParameter(argc, argv);
    if (po::hasOption(parameterList, "--devicename"))
    {
        const auto maybeDevicename = po::getOption(parameterList, "--devicename");
        if (!maybeDevicename.has_value() || maybeDevicename->length() == 0)
        {
            std::cerr << "Invalid or no parameter to '--devicename' given" << std::endl;
            return -1;
        }
        params.devicename = *maybeDevicename;
    }
    if (po::hasOption(parameterList, "--baudrate"))
    {
        const auto maybeBaudrate = po::getOption(parameterList, "--baudrate");
        if (!maybeBaudrate.has_value() || maybeBaudrate->length() == 0)
        {
            std::cerr << "Invalid or no parameter to '--baudrate' given" << std::endl;
            return -1;
        }
        params.baud_rate = atoi(std::string{*maybeBaudrate}.c_str());
    }


    if(!open_serial_port(params.devicename)) {
        throw std::runtime_error("Could not open serial port " + params.devicename);
    }

    set_serial_properties(params.baud_rate);
    printf("Opened device %s with baudrate %d\n", params.devicename.c_str(), params.baud_rate);

    Command cmd;
    while (true)
    {
        sleep(1);
    }
    ::close(serial_fd_);
    return 0;
}
