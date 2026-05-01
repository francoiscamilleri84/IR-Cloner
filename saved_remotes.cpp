#include "saved_remotes.h"
#include "remote_handler.h"
#include "remotes.h"
#include <string.h>
#include "main.h"
#include "globals.h"
#include "display_utils.h"
#include "input_utils.h"
#include "menu_handler.h"

MenuItem savedRemotesMenu[] = {
  {"SD Card", LIST_SD_CARD_REMOTES},
  {"LittleFS", LIST_LITTLE_FS_REMOTES}
};

const int savedRemotesMenuTotalItems = sizeof(savedRemotesMenu) / sizeof(savedRemotesMenu[0]);


void listRemoteFiles(fs::FS &fileLocation) {
  File dir = fileLocation.open("/ir");
  if (!dir || !dir.isDirectory()) {
    Serial.println("Failed to open /ir");
    return;
  }

  File file = dir.openNextFile();
  while (file) {
    if (!file.isDirectory()) {
      Serial.println(file.name());
    }
    file = dir.openNextFile();
  }
}


void runSavedRemotesView() {
  startFrame();

  if (changeView(REMOTE_MODE, KEY_BACK)) {
    endFrame();
    menuRedraw = false;
    return;
  }

  handleMenuInput(savedRemotesMenu, savedRemotesMenuTotalItems);
  drawMenu(currentState, savedRemotesMenu, savedRemotesMenuTotalItems);

  endFrame();
  menuRedraw = false;
}

void listSavedRemotesView(){

  if (currentState = LIST_SD_CARD_REMOTES){

      listRemoteFiles(SD);

  } else if (currentState = LIST_LITTLE_FS_REMOTES){

    listRemoteFiles(LittleFS);

  }


}






