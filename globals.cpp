#include "globals.h"

AppState currentState = APP_SPLASH;
bool menuRedraw = true;



String getTitleByState(AppState state) {
    switch (state) {
        case APP_SPLASH: return "Press any key to start";
        case MAIN_MENU_MODE: return "CARDPUTER:~/IR_TOOL";
        case REMOTE_MODE:    return "REMOTES";
        case QUICK_CAPTURE_MODE: return "QUICK CAPTURE";
        case CREATE_REMOTE_MODE:  return "CREATE REMOTE";
        case SAVED_REMOTES_MODE:  return "SAVED REMOTES";
        case SPAM_MODE:      return "SPAM SIGNALS";
        case SETTINGS_MODE:  return "SETTINGS"; 
        default:             return "CARDPUTER:~/IR_TOOL";
    }
}





