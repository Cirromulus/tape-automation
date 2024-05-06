#pragma once

#include <HKWire.h>
#include <optional>

void
setupGPIO();

std::optional<HKWire::Payload>
try_read_message_from_device(std::optional<unsigned> timeout_in_ms = std::nullopt);

void
write_message_to_device(const HKWire::Payload& message, std::optional<unsigned> timeout_in_ms = std::nullopt);
