#include "saved_remotes.h"

#include <string.h>
#include <LittleFS.h>
#include <SD.h>

MenuItem savedRemotesMenu[] = {
    {"SD Card", AppState::ListSDCardRemotes, true},
    {"LittleFS", AppState::ListLittleFSRemotes, true}
};

const int savedRemotesMenuTotalItems =
    sizeof(savedRemotesMenu) / sizeof(savedRemotesMenu[0]);

String remoteNames[maxRemotes];
MenuItem remoteMenuItems[maxRemotes];
int remoteMenuItemCount = 0;

void buildRemoteFileMenu(fs::FS &fileLocation) {
    remoteMenuItemCount = 0;

    File dir = fileLocation.open("/ir");
    if (!dir || !dir.isDirectory()) {
        Serial.println("Failed to open /ir");
        return;
    }

    File file = dir.openNextFile();

    while (file && remoteMenuItemCount < maxRemotes) {
        if (!file.isDirectory()) {
            String fullName = file.name();

            if (fullName.endsWith(".ir")) {
                int slash = fullName.lastIndexOf('/');
                String remoteName =
                    (slash >= 0) ? fullName.substring(slash + 1) : fullName;

                remoteNames[remoteMenuItemCount] = remoteName;

                AppState targetState =
                    (&fileLocation == &SD)
                        ? AppState::ViewRemoteSD
                        : AppState::ViewRemoteLittleFS;

                remoteMenuItems[remoteMenuItemCount] = MenuItem{
                    remoteNames[remoteMenuItemCount].c_str(),
                    targetState,
                    true
                };

                remoteMenuItemCount++;
            }
        }

        file = dir.openNextFile();
    }
}

void renderSavedRemotesView() {
    startFrame();

    if (changeView(AppState::Remotes, KEY_ESC)) {
        endFrame();
        menuRedraw = false;
        return;
    }

    drawMenu(savedRemotesMenu, savedRemotesMenuTotalItems);
    handleMenuInput(savedRemotesMenu, savedRemotesMenuTotalItems);

    endFrame();
    menuRedraw = false;
}

void listSavedRemotesView(fs::FS &fileLocation) {
    startFrame();

    if (changeView(AppState::SavedRemotes, KEY_ESC)) {
        endFrame();
        menuRedraw = false;
        return;
    }

    if (menuRedraw) {
        buildRemoteFileMenu(fileLocation);
    }

    if (remoteMenuItemCount == 0) {
        Canvas.setCursor(bodyTextXPosition, bodyTextYPosition);
        Canvas.println("No .ir files found");
        Canvas.println("Press [ESC] to go back");
    } else {
        drawMenu(remoteMenuItems, remoteMenuItemCount);
        handleMenuInput(remoteMenuItems, remoteMenuItemCount);
    }

    endFrame();
    menuRedraw = false;
}