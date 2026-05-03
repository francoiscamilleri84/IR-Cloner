#pragma once
#include <Arduino.h>

const uint16_t maxRawSamples = 750;
extern bool isCaptured;

struct storedIrSignal {
    uint8_t protocol;
    uint16_t address;
    uint32_t command;
    uint32_t decodedRawData;
    uint16_t rawBuffer[maxRawSamples];
    uint16_t rawLength;
    bool valid;
};

extern storedIrSignal lastIrSignal;
