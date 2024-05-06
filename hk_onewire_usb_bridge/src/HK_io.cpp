#include <config.hpp>

#include "HK_io.hpp"
#include <pico/stdlib.h>


void
initPinOutput(unsigned pin)
{
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_OUT);
}

void
initPinInput(unsigned pin)
{
    gpio_init(pin);
    gpio_set_dir(pin, GPIO_IN);
}

void
setupGPIO()
{
    // TODO: Proper
    initPinInput(config::PinDataIn);
    initPinInput(config::PinBusyIn);
    initPinOutput(config::PinDataOut);
    initPinOutput(config::PinBusyOut);
}

std::optional<HKWire::Payload>
try_read_message_from_device(std::optional<unsigned> timeout_in_ms)
{
    auto state = HKWire::WordState::start;
    // TODO
    return std::nullopt;
}

void
write_message_to_device(const HKWire::Payload& message, std::optional<unsigned> timeout_in_ms)
{
    // TODO
}