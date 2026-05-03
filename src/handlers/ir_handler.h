#ifndef IR_HANDLER_H
#define IR_HANDLER_H

#include "../core/definitions.h"
#include "../core/globals.h"
#include "../models/ir_signal.h"
#include "../utils/display_utils.h"
#include "../utils/sound_utils.h"


void initIR();
void resumeIR();
bool decodeIR();
void captureIrSignal();
void sendIR();
bool hasCapturedIrSignal();
void resetCaptureState();
void processCapture();
bool isIRSignalValid();


#endif