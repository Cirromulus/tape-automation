#include <config.hpp>
#include <protocol.hpp>
#include <networkOrder.hpp>
#include "HK_io.hpp"

#include <stdio.h>
#include <array>
#include <pico/stdlib.h>
#include <hardware/structs/usb.h> // of pico
#include <pico/multicore.h>
#include <optional>


std::optional<Command>
try_read_command_from_host();

void
handleHKWireMessages();

void
handleUSBCommands();

bool
isUSBHostConnected()
{
    return usb_hw->sie_status & USB_SIE_STATUS_CONNECTED_BITS;
}

int main() {
    setup_default_uart();
    stdio_init_all();

    setupGPIO();

    multicore_launch_core1(handleHKWireMessages);

    handleUSBCommands();

    return 0;
}

void
handleUSBCommands()
{
    while (true)
    {
        const auto command = try_read_command_from_host();
        if(command)
        {
            write_message_to_device(command->message);
        }
    };
}

void
handleHKWireMessages()
{
    while(true)
    {
        const auto maybeCommand = try_read_message_from_device();
        if (maybeCommand)
        {
            const auto serialized = maybeCommand->getSerialized();
            const auto serializedNO = swapIfNotNetworkOrder(serialized);

            unsigned p = 0;
            while (p < sizeof(decltype(serializedNO)))
            {
                putchar_raw(serializedNO >> (p * 8) & 0xFF);
            }
        }
    }
}

std::optional<Command>
try_read_command_from_host()
{
    SerializedCommand buf = 0;
    unsigned p = 0;

    while (p < sizeof(decltype(buf)))
    {
        const auto maybeChar = getchar_timeout_us(1000);    // 1 ms
        if (maybeChar == PICO_ERROR_TIMEOUT)
            return std::nullopt;

        buf |= maybeChar << (p * 8);
        p++;
    }
    return Command{HKWire::Payload{swapIfNotNetworkOrder(buf)}};
}