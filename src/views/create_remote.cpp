#include "create_remote.h"
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

static RemoteState remoteState = RemoteState::CaptureSignal;

static RemoteStateMenuItem nextActionMenu[] = {
    {"Create new button", RemoteState::CaptureSignal, true},
    {"Save remote",       RemoteState::SaveRemote,   true}
};

static RemoteStateMenuItem saveLocationMenu[] = {
    {"SD Card",   RemoteState::Complete, sdCardAvailable},
    {"LittleFS",  RemoteState::Complete, true}
};

static const int nextActionMenuCount = sizeof(nextActionMenu) / sizeof(nextActionMenu[0]);

static const int saveLocationMenuCount = sizeof(saveLocationMenu) / sizeof(saveLocationMenu[0]);


static void resetCreateRemoteFlow() {
    remoteState = RemoteState::CaptureSignal;
    resetCaptureState();
    keyboardInputData = "";
    menuSelectedIndex = 0;
    topVisibleIndex = 0;
}

static int stateSwitchMenu(RemoteStateMenuItem items[], int itemCount) {
    if (itemCount <= 0) return -1;

    for (int i = 0; i < maxVisibleItems; i++) {
        int itemIndex = topVisibleIndex + i;
        if (itemIndex >= itemCount) break;

        bool isSelected = (itemIndex == menuSelectedIndex);
        int yPos = bodyTextYPosition + (i * menuSpacing);

        Canvas.setCursor(bodyTextXPosition, yPos);
        Canvas.setTextColor(
            items[itemIndex].enabled
                ? (isSelected ? highlightedTextColor : headerTextColor)
                : disabledTextColor,
            fillScreenColor
        );

        Canvas.printf("%s%s", isSelected ? "> " : "  ", items[itemIndex].label);
    }

    if (!isKeyEvent()) return -1;

    int oldIndex = menuSelectedIndex;

    if (isUpPressed()) {
        menuSelectedIndex = (menuSelectedIndex - 1 + itemCount) % itemCount;
    } else if (isDownPressed()) {
        menuSelectedIndex = (menuSelectedIndex + 1) % itemCount;
    } else if (isEnterPressed()) {
        if (!items[menuSelectedIndex].enabled) return -1;

        int selectedIndex = menuSelectedIndex;
        remoteState = items[selectedIndex].targetState;
        menuSelectedIndex = 0;
        topVisibleIndex = 0;
        menuRedraw = true;
        return selectedIndex;
    }

    if (menuSelectedIndex < topVisibleIndex) {
        topVisibleIndex = menuSelectedIndex;
    } else if (menuSelectedIndex >= topVisibleIndex + maxVisibleItems) {
        topVisibleIndex = menuSelectedIndex - maxVisibleItems + 1;
    }

    if (oldIndex != menuSelectedIndex) {
        menuRedraw = true;
    }

    return -1;
}


void renderCreateRemoteView() {
    M5Cardputer.update();
    startFrame();
    if (changeView(AppState::Remotes, KEY_ESC)) {
        resetCreateRemoteFlow();
        endFrame();
        return;
    }
    
    saveLocationMenu[0].enabled = sdCardAvailable;

    switch (remoteState) {
        case RemoteState::CaptureSignal:
            createDisp();
            processCapture();

            if (!isCaptured) {
                renderCaptureWaitingView();
            } else {
                renderCapturedSignalView();
                renderCreateRemoteCapturedTextView();
                if (isKeyEvent() && isEnterPressed()) {
                    remoteState = RemoteState::SaveButton;
                    menuRedraw = true;
                }
                if (M5Cardputer.BtnA.wasPressed()) {
                    resetCaptureState();
                    remoteState = RemoteState::CaptureSignal;
                }
            }
            break;

        case RemoteState::SaveButton:{
            Canvas.setCursor(bodyTextMarginLeft, bodyTextMarginTop);
            Canvas.setTextSize(1);
            Canvas.println("Button name:");
            int inputY = Canvas.getCursorY() + 4;
            inputBox(bodyTextMarginLeft, inputY, 220, 30, keyboardInputData);

            bool saveButtonSubmitted = handleKeyboardInput();
            if (saveButtonSubmitted) {
                setCurrentRemoteName(keyboardInputData.c_str());
                createRemoteButton(keyboardInputData.c_str(), lastIrSignal);
                keyboardInputData = "";
                remoteState = RemoteState::SaveButtonConfirmed;
            }

            break;

        }
            

        case RemoteState::SaveButtonConfirmed:{
            drawOverlay("Continue", "Button Saved");
            if (isKeyEvent() && isEnterPressed()) {
                resetCaptureState();
                remoteState = RemoteState::ChooseNextAction;
            }
            break;
        }
        case RemoteState::ChooseNextAction:{
            stateSwitchMenu(nextActionMenu, nextActionMenuCount);
            break;
        }
        case RemoteState::SaveRemote:{
            Canvas.setCursor(bodyTextMarginLeft, bodyTextMarginTop);
            Canvas.setTextSize(1);
            Canvas.println("Remote name:");
            int inputY = Canvas.getCursorY() + 4;
            inputBox(bodyTextMarginLeft, inputY, 220, 30, keyboardInputData);
            bool saveRemoteSubmitted = handleKeyboardInput();
            if (saveRemoteSubmitted) {
                setCurrentRemoteName(keyboardInputData.c_str());
                keyboardInputData = "";
                remoteState = RemoteState::SaveLocation;
            }
            break;
        }
        case RemoteState::SaveLocation:{
            int selected = stateSwitchMenu(saveLocationMenu, saveLocationMenuCount);

            if (selected == 0) {
                saveRemote(SD);
                remoteState = RemoteState::Complete;
                
            } else if (selected == 1) {
                saveRemote(LittleFS);
                remoteState = RemoteState::Complete;
            }
            break;
        }

        case RemoteState::Complete:{
            drawOverlay("Continue", "Remote Saved");
            if (isKeyEvent() && isEnterPressed()) {
                resetCreateRemoteFlow();
                currentState = AppState::Remotes;
            }
            break;
        }
    }

    endFrame();
}
