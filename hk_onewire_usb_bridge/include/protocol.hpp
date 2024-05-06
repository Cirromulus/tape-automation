#pragma once
#include <HKWire.h>

// TODO
struct Command
{
    // Are more than just the payload needed? this would necessitate a cmd here
    HKWire::Payload message;
};

using SerializedCommand = HKWire::Payload::SerializedType;     // TODO