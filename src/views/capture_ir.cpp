#include "capture_ir.h"

#include "captured_signal.h"
#include "../core/globals.h"
#include "../handlers/remote_handler.h"
#include "../handlers/ir_handler.h"
#include "../handlers/menu_handler.h"
#include "../utils/display_utils.h"
#include "../utils/input_utils.h"
#include "../utils/storage_utils.h"
#include "../views/captured_signal.h"
#include <LittleFS.h>
#include <SD.h>

void renderQuickCaptureView() {
    if (menuRedraw) {
        resetCaptureState();
        menuRedraw = false;
    }

    startFrame();
    createDisp();

    if (changeView(AppState::Remotes, KEY_ESC)) {
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
    }

    if (!isCaptured) {
        renderCaptureWaitingView();
    } else {
        renderCapturedSignalView();
        renderQuickCapturedTextView();
    }

    endFrame();
}