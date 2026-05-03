#include "captured_signal.h"

#include "../core/definitions.h"
#include "../core/globals.h"
#include "../handlers/ir_handler.h"
#include "../utils/display_utils.h"
#include "../utils/sound_utils.h"
#include <M5Cardputer.h>

void renderCaptureWaitingView() {
    Canvas.setTextColor(bodyTextColor);
    Canvas.setTextSize(bodyFontSize);
    Canvas.setCursor(bodyTextMarginLeft, bodyTextMarginTop);
    Canvas.println("Aim remote at receiver.");
    Canvas.setCursor(bodyTextMarginLeft, bodyTextMarginTop + 20);
    Canvas.println("Press remote button to capture.");
    Canvas.setCursor(bodyTextMarginLeft, bodyTextMarginTop + 40);
    Canvas.println("Awaiting Signal...");
}

void renderCapturedSignalView() {
    Canvas.setTextColor(highlightedTextColor);
    Canvas.setTextSize(headerFontSize);
    Canvas.printf("Command: %08lX", (unsigned long)lastIrSignal.command);
    Canvas.setCursor(bodyTextMarginLeft, bodyTextMarginTop + 25);
    Canvas.printf("Protocol: %d", lastIrSignal.protocol);
}

void renderQuickCapturedTextView() {
    Canvas.setCursor(bodyTextMarginLeft, bodyTextMarginTop + 55);
    Canvas.setTextColor(bodyTextColor);
    Canvas.setTextSize(1);
    Canvas.println("[ENTER] Replay signal");
    Canvas.setCursor(bodyTextMarginLeft, bodyTextMarginTop + 75);
    Canvas.println("[G0] Capture new signal");
}

void renderCreateRemoteCapturedTextView() {
    Canvas.setCursor(bodyTextMarginLeft, bodyTextMarginTop + 55);
    Canvas.setTextColor(bodyTextColor);
    Canvas.setTextSize(1);
    Canvas.println("[ENTER] Save button");
    Canvas.setCursor(bodyTextMarginLeft, bodyTextMarginTop + 75);
    Canvas.println("[G0] Capture new signal");
}