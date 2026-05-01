#include "ir_handler.h"
#include "display_utils.h"
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
  lastIrSignal.rawLength = 0;
  lastIrSignal.valid = true;
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

void generateReceivedTone() {
  M5Cardputer.Speaker.tone(2000, 100);
  delay(250);
}

void generateSendTone() {
  M5Cardputer.Speaker.tone(1000, 100);
  delay(250);
}

void resetCaptureState() {
  isCaptured = false;
  lastIrSignal.valid = false;
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

void drawCaptureWaitingView() {
  Canvas.println("Aim remote at receiver.");
  Canvas.setCursor(bodyTextMarginLeft, bodyTextMarginTop + 20);
  Canvas.println("Press remote button to capture.");
  Canvas.setCursor(bodyTextMarginLeft, bodyTextMarginTop + 40);
  Canvas.println("Awaiting Signal...");
}

void drawCapturedSignalView() {
  Canvas.setTextColor(highlightedTextColor);
  Canvas.setTextSize(headerFontSize);
  Canvas.printf("Command: %08lX", (unsigned long)lastIrSignal.command);
  Canvas.setCursor(bodyTextMarginLeft, bodyTextMarginTop + 25);
  Canvas.printf("Protocol: %d", lastIrSignal.protocol);
}

bool isIRSignalValid() {
  auto& data = IrReceiver.decodedIRData;

  bool protocolKnown = data.protocol != UNKNOWN;
  bool hasDecodedValue =
      data.address != 0 ||
      data.command != 0 ||
      data.decodedRawData != 0;
      
  return (protocolKnown && hasDecodedValue);
}




















