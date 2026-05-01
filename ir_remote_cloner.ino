#include "globals.h"
#include "definitions.h"
#include "display_utils.h"
#include "input_utils.h"
#include "menu_handler.h"
#include "main.h"
#include "remotes.h"
#include "saved_remotes.h"
#include "ir_handler.h"
#include "capture_ir.h"
#include "create_remote.h"
#include "storage_handler.h"
#include "splash_sprite.h"

void setup() {
    auto cfg = M5.config();
    M5Cardputer.begin(cfg);
    Serial.begin(115200);
    delay(200);
    initIR();
    initDisplay();
    
    if (!LittleFS.begin(true)) {
        Serial.println("LittleFS Mount Failed");
    } else {
        Serial.println("LittleFS ready");
    }
    SPI.begin(SD_SPI_SCK_PIN, SD_SPI_MISO_PIN, SD_SPI_MOSI_PIN, SD_SPI_CS_PIN);

    if (!SD.begin(SD_SPI_CS_PIN)) {
        Serial.println("SD Card Mount Failed");
    } else {
        Serial.println("SD Card ready");
    }
    menuRedraw = true; 
}

void loop() {
    M5Cardputer.update();
    AppState lastState = currentState;
    if (currentState == APP_SPLASH && M5Cardputer.Keyboard.isChange()) {
      if (M5Cardputer.Keyboard.isPressed() > 0) {
        currentState = MAIN_MENU_MODE;
      }
    }
    switch (currentState) {
        case APP_SPLASH:
            runSplashView();
        break;
        case MAIN_MENU_MODE:
            runMainMenuView();
        break;

        case REMOTE_MODE:
            runRemotesMenuView();
        break;

        case QUICK_CAPTURE_MODE:
            runQuickCaptureView();
        break;

        case CREATE_REMOTE_MODE:
            runCreateRemoteView();
        break;
        
        case SAVED_REMOTES_MODE:
            runSavedRemotesView();
        break;

        case LIST_LITTLE_FS_REMOTES:
            listSavedRemotesView();
        break;
        
        case LIST_SD_CARD_REMOTES:
            listSavedRemotesView();
        break;


        case SPAM_MODE:
            runPlaceholderView("SPAM SIGNALS");
        break;

        case SETTINGS_MODE:
        
            runPlaceholderView("SETTINGS/SAVED");
        break;
            
        default:
            runMainMenuView();
        break;
    }

    if (currentState != lastState) {
        menuRedraw = true;

    }
}

//placeholder view - remove when complete

void runPlaceholderView(String featureName) {
    if (M5Cardputer.Keyboard.isKeyPressed(KEY_BACK)) {
        currentState = MAIN_MENU_MODE;
        menuRedraw = true;
        return;
    }

    if (menuRedraw) {
        startFrame();
        Canvas.setCursor(10, 40);
        Canvas.setTextColor(headerTextColor);
        Canvas.print("Coming Soon..."); 
        endFrame();
        menuRedraw = false;
    }
}