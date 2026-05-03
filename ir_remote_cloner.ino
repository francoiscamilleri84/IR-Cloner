// --- CORE --- 
#include "src/core/definitions.h"
#include "src/core/globals.h"
#include "src/core/main.h"
#include "src/core/splash_sprite.h"

// --- HANDlERS ---
#include "src/handlers/ir_handler.h"
#include "src/handlers/menu_handler.h"


// --- UTILS --- 
#include "src/utils/display_utils.h"
#include "src/utils/storage_utils.h"
#include "src/utils/input_utils.h"

// --- VIEWS --- 
#include "src/views/capture_ir.h"
#include "src/views/captured_signal.h"
#include "src/views/create_remote.h"
#include "src/views/remotes.h"
#include "src/views/saved_remotes.h"
#include "src/views/splash.h"
#include "src/views/view_remote.h"


// --- LIBRARIES ---
#include <LittleFS.h>
#include <SPI.h>
#include <SD.h>
#include <string.h>


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
    sdCardAvailable = false;
    } else {
        Serial.println("SD Card ready");
        sdCardAvailable = true;
    }
    menuRedraw = true; 
}

void loop() {
    M5Cardputer.update();
    AppState lastState = currentState;
    
    switch (currentState) {
        case AppState::Splash:
            renderSplashView();
        break;
        case AppState::MainMenu:
            renderMainMenuView();
        break;

        case AppState::Remotes:
            renderRemotesMenuView();
        break;

        case AppState::QuickCapture:
            renderQuickCaptureView();
        break;

        case AppState::CreateRemote:
            renderCreateRemoteView();
        break;
        
        case AppState::SavedRemotes:
            renderSavedRemotesView();
        break;

        case AppState::ListLittleFSRemotes:
             listSavedRemotesView(LittleFS);
        break;
        
        case AppState::ListSDCardRemotes:
             listSavedRemotesView(SD);
        break;

        case AppState::ViewRemoteSD:
            renderRemoteView(SD, selectedRemotePath.c_str());
        break;

        case AppState::ViewRemoteLittleFS:
            renderRemoteView(LittleFS, selectedRemotePath.c_str());
        break;

        case AppState::SpamSignals:
            runPlaceholderView("SPAM SIGNALS");
        break;

        case AppState::Settings:
            runPlaceholderView("SETTINGS/SAVED");
        break;
            
        default:
            renderMainMenuView();
        break;
    }

    if (currentState != lastState) {
        menuRedraw = true;

    }
}

//placeholder view - remove when complete

void runPlaceholderView(String featureName) {
    if (M5Cardputer.Keyboard.isKeyPressed(KEY_ESC)) {
        currentState = AppState::MainMenu;
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