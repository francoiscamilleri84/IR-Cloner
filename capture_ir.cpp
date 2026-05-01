#include "capture_ir.h"
#include "main.h"
#include "globals.h"
#include "display_utils.h"
#include "input_utils.h"
#include "menu_handler.h"
#include "ir_handler.h"

void drawQuickCapturedTextView(){
  Canvas.setCursor(bodyTextMarginLeft, bodyTextMarginTop + 55);
  Canvas.setTextColor(bodyTextColor);
  Canvas.setTextSize(bodyFontSize);
  Canvas.println("Press [Enter] to replay signal");
  Canvas.setCursor(bodyTextMarginLeft, bodyTextMarginTop + 75);
  Canvas.println("Press [G0] to capture new signal");
}


void runQuickCaptureView() {

  if (menuRedraw) {
    resetCaptureState();
    menuRedraw = false;
  }

  startFrame();
  createDisp();

  if (changeView(REMOTE_MODE, KEY_BACK)) {
    endFrame();
    resetCaptureState();
    return;
  }

  processCapture();

  if (isCaptured &&
    M5Cardputer.Keyboard.isChange() &&
    M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER)) {
    sendIR();
    generateSendTone();
  }

  if (isCaptured && M5Cardputer.BtnA.wasPressed()) {
    resetCaptureState();
    drawCapturedSignalView();
  }

  if (!isCaptured) {
    drawCaptureWaitingView();
  } else {
    drawCapturedSignalView();
    drawQuickCapturedTextView();
  }

  endFrame();
}