#include "M5Cardputer.h"
#include "main.h"
#include "globals.h"
#include "display_utils.h"
#include "menu_handler.h"

MenuItem mainMenu[] = {
  {"Remotes", REMOTE_MODE},
  {"Spam Mode", SPAM_MODE},
  {"Settings", SETTINGS_MODE}
};

const int mainMenuTotalItems = sizeof(mainMenu) / sizeof(mainMenu[0]);

void runMainMenuView() {
  startFrame();
  changeView(MAIN_MENU_MODE, KEY_BACK);
  handleMenuInput(mainMenu, mainMenuTotalItems);
  drawMenu(currentState, mainMenu, mainMenuTotalItems);
  endFrame();
  menuRedraw = false;
}
