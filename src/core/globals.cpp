#include "globals.h"

AppState currentState = AppState::Splash;
String keyboardInputData = "";
String selectedRemotePath = "";
String selectedRemoteName = "";
bool menuRedraw = false;
bool sdCardAvailable = false;

String getTitleByState(AppState state) {
    switch (state) {
        case AppState::Splash:              return "Press any key to start";
        case AppState::MainMenu:            return "CARDPUTER:~/IR_TOOL";
        case AppState::Remotes:             return "REMOTES";
        case AppState::QuickCapture:        return "QUICK CAPTURE";
        case AppState::CreateRemote:        return "CREATE REMOTE";
        case AppState::SavedRemotes:        return "SAVED REMOTES";
        case AppState::ViewRemoteSD:        return "VIEW REMOTE";
        case AppState::ViewRemoteLittleFS:  return "VIEW REMOTE";
        case AppState::SpamSignals:         return "SPAM SIGNALS";
        case AppState::Settings:            return "SETTINGS";
        case AppState::ListLittleFSRemotes: return "Little FS";
        case AppState::ListSDCardRemotes:   return "SD Card";
    }
    return "CARDPUTER:~/IR_TOOL";
}