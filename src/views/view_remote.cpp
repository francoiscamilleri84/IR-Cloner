#include "view_remote.h"

#include "../core/globals.h"
#include "../handlers/remote_handler.h"
#include "../handlers/ir_handler.h"
#include "../handlers/menu_handler.h"
#include "../utils/display_utils.h"
#include "../utils/input_utils.h"
#include "../utils/storage_utils.h"
#include <LittleFS.h>
#include <SD.h>


void renderRemoteView(fs::FS& fs, const char* filepath) {
    startFrame();

    if (changeView(AppState::SavedRemotes, KEY_ESC)) {
        endFrame();
        menuRedraw = false;
        return;
    }

    File file = fs.open(filepath, FILE_READ);
    if (!file) {
        Canvas.setCursor(bodyTextXPosition, bodyTextYPosition);
        Canvas.printf("Failed to open:\n%s", filepath);
        endFrame();
        return;
    }

    Canvas.setTextColor(bodyTextColor);
    Canvas.setTextSize(bodyFontSize);
    Canvas.setCursor(bodyTextXPosition, bodyTextYPosition);
    Canvas.printf("Filename: %s\n\n", selectedRemoteName.c_str());
    Canvas.setCursor(bodyTextXPosition, bodyTextYPosition + 10);
    Canvas.setTextWrap(true, false);
    int lineheight = 1;
    while (file.available()) {
        Canvas.setCursor(bodyTextXPosition, bodyTextYPosition + (10 * lineheight));
        String line = file.readStringUntil('\n');
        Canvas.println(line);
        lineheight ++;
    }

    file.close();
    endFrame();
    menuRedraw = false;
}