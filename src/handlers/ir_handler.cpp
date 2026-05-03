#include "ir_handler.h"
#include "../core/definitions.h"
#include <IRremote.hpp>

storedIrSignal lastIrSignal = {0, 0, 0, 0, {0}, 0, false};
bool isCaptured = false;

void initIR() {
    IrReceiver.begin(irRxPin, ENABLE_LED_FEEDBACK);
    IrSender.begin(irTxPin);
    delay(50);
}

void resumeIR() {
    IrReceiver.resume();
}

bool decodeIR() {
    return IrReceiver.decode();
}

bool hasCapturedIrSignal() {
    return lastIrSignal.valid;
}

void captureIrSignal() {
    lastIrSignal.protocol = IrReceiver.decodedIRData.protocol;
    lastIrSignal.address = IrReceiver.decodedIRData.address;
    lastIrSignal.command = IrReceiver.decodedIRData.command;
    lastIrSignal.decodedRawData = IrReceiver.decodedIRData.decodedRawData;
    lastIrSignal.valid = true;

    uint16_t rawLength = IrReceiver.irparams.rawlen;
    if (rawLength > maxRawSamples) {
        rawLength = maxRawSamples;
    }

    lastIrSignal.rawLength = rawLength;

    for (uint16_t i = 0; i < rawLength; i++) {
        lastIrSignal.rawBuffer[i] = IrReceiver.irparams.rawbuf[i];
    }
}

void sendIR() {
    if (!lastIrSignal.valid) return;

    delay(250);

    switch (lastIrSignal.protocol) {
        case NEC:
            IrSender.sendNEC(lastIrSignal.address, lastIrSignal.command, 0);
            break;

        case SAMSUNG:
            IrSender.sendSamsung(lastIrSignal.address, lastIrSignal.command, 0);
            break;

        case SONY:
            IrSender.sendSony(lastIrSignal.address, lastIrSignal.command, 0);
            break;

        case LG:
            IrSender.sendLG(lastIrSignal.address, lastIrSignal.command, 0);
            break;

        case JVC:
            IrSender.sendJVC(lastIrSignal.address, lastIrSignal.command, 0);
            break;

        case UNKNOWN:
        case PULSE_WIDTH:
        case PULSE_DISTANCE:
            if (lastIrSignal.rawLength > 0) {
                IrSender.sendRaw(lastIrSignal.rawBuffer, lastIrSignal.rawLength, 38);
            }
            break;

        default:
            break;
    }
}

void resetCaptureState() {
    isCaptured = false;
    lastIrSignal.valid = false;
    lastIrSignal.rawLength = 0;
    resumeIR();
}

void processCapture() {
    if (!isCaptured && decodeIR()) {
        if (isIRSignalValid()) {
            captureIrSignal();
            isCaptured = true;
            generateReceivedTone();
            resumeIR();
        }
    }
}

bool isIRSignalValid() {
    auto& data = IrReceiver.decodedIRData;

    bool protocolKnown = data.protocol != UNKNOWN;
    bool hasDecodedValue =
        data.address != 0 ||
        data.command != 0 ||
        data.decodedRawData != 0;

    bool hasRawData = IrReceiver.irparams.rawlen > 0;

    return (protocolKnown && hasDecodedValue) || hasRawData;
}