#ifndef APP_STATE_H
#define APP_STATE_H

enum class AppState {
    CreateRemote,
    CreateRemoteSaveLocation,
    ListLittleFSRemotes,
    ListSDCardRemotes,
    MainMenu,
    QuickCapture,
    Remotes,
    SavedRemotes,
    ViewRemoteSD,
    ViewRemoteLittleFS,
    Settings,
    SpamSignals,
    Splash
};

#endif