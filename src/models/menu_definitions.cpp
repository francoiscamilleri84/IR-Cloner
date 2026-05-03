#include "menu_definitions.h"

MenuItem mainMenuItems[] = {
    {"Remotes", AppState::Remotes},
    {"Quick Capture", AppState::QuickCapture},
    {"Settings", AppState::Settings}
};

const int mainMenuItemCount = sizeof(mainMenuItems) / sizeof(mainMenuItems[0]);

MenuItem savedRemotesMenuItems[] = {
    {"Little FS", AppState::ListLittleFSRemotes, true},
    {"SD Card", AppState::ListSDCardRemotes, false}
};

const int savedRemotesMenuItemCount = sizeof(savedRemotesMenuItems) / sizeof(savedRemotesMenuItems[0]);

MenuItem saveLocationMenuItems[] = {
    {"Little FS", AppState::CreateRemoteSaveLocation, true},
    {"SD Card", AppState::CreateRemoteSaveLocation, false}
};

const int saveLocationMenuItemCount = sizeof(saveLocationMenuItems) / sizeof(saveLocationMenuItems[0]);

extern MenuItem mainMenuItems[];
extern const int mainMenuItemCount;

extern MenuItem savedRemotesMenuItems[];
extern const int savedRemotesMenuItemCount;

extern MenuItem saveLocationMenuItems[];
extern const int saveLocationMenuItemCount;