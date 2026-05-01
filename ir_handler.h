#ifndef IR_HANDLER_H
#define IR_HANDLER_H

#include "globals.h"

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

void initIR();
void resumeIR();
bool decodeIR();
void generateReceivedTone();
void generateSendTone();
void captureIrSignal();
void sendIR();
bool hasCapturedIrSignal();
void resetCaptureState();
void processCapture();
void drawCaptureWaitingView();
void drawCapturedSignalView();
bool isIRSignalValid();

extern storedIrSignal lastIrSignal;

#endif 