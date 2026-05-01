#ifndef GLOBALS_H
#define GLOBALS_H

#include "definitions.h"
#include <LittleFS.h>
#include <SD.h>


enum AppState {
    APP_SPLASH,
    MAIN_MENU_MODE,
    REMOTE_MODE,
    SPAM_MODE,
    SETTINGS_MODE,
    QUICK_CAPTURE_MODE,
    CREATE_REMOTE_MODE, 
    SAVED_REMOTES_MODE,
    LIST_LITTLE_FS_REMOTES,
    LIST_SD_CARD_REMOTES

};

struct MenuItem {
    String label;
    AppState targetState;
};

extern String getTitleByState(AppState state);
void handleKeyboardInput(char *inputBuffer, size_t bufferSize);

extern AppState currentState;
extern String getTitleByState(AppState state);
extern bool menuRedraw;

#endif