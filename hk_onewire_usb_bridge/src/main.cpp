#include <config.hpp>
#include <protocol.hpp>
#include <networkOrder.hpp>

#include <stdio.h>
#include <array>
#include <pico/stdlib.h>
#include <hardware/structs/usb.h> // of pico
#include <pico/multicore.h>
#include <optional>


std::optional<Command>
try_read_command();

void
handleHKWireCommands()
{
    while(true)
    {
        // TODO
        break;
    }
}

bool
isUSBHostConnected()
{
    return usb_hw->sie_status & USB_SIE_STATUS_CONNECTED_BITS;
}

int main() {
    setup_default_uart();
    stdio_init_all();

    multicore_launch_core1(handleHKWireCommands);

    while (true)
    {
        // const auto vorher = get_absolute_time();
        const auto command = try_read_command();
        if(command)
        {
            // TODO
        }
    };

    return 0;
}

std::optional<Command>
try_read_command()
{
    SerializedCommand buf = 0;
    unsigned p = 0;

    while (p < sizeof(decltype(buf)))
    {
        auto maybeChar = getchar_timeout_us(1000);    // 1 ms
        if (maybeChar == PICO_ERROR_TIMEOUT)
            return std::nullopt;

        buf |= maybeChar << (p * 8);
        p++;
    }
    // TODO: NTOH
    return Command(swapIfNotNetworkOrder(buf));
}