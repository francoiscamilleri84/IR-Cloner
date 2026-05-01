#include "remotes.h"
#include "remote_handler.h"
#include <string.h>
#include "main.h"
#include "globals.h"
#include "display_utils.h"
#include "input_utils.h"
#include "menu_handler.h"
#include "ir_handler.h"



MenuItem remotesMenu[] = {
  {"Quick Capture", QUICK_CAPTURE_MODE},
  {"Create Remote", CREATE_REMOTE_MODE},
  {"Saved Remotes", SAVED_REMOTES_MODE}
};

const int remotesMenuTotalItems = sizeof(remotesMenu) / sizeof(remotesMenu[0]);


void runRemotesMenuView() {
  startFrame();

  if (changeView(MAIN_MENU_MODE, KEY_BACK)) {
    endFrame();
    menuRedraw = false;
    return;
  }

  handleMenuInput(remotesMenu, remotesMenuTotalItems);
  drawMenu(currentState, remotesMenu, remotesMenuTotalItems);

  endFrame();
  menuRedraw = false;
}





