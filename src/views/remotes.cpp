#include "remotes.h"


MenuItem remotesMenu[] = {
  {"Quick Capture", AppState::QuickCapture, true},
  {"Create Remote", AppState::CreateRemote, true},
  {"Saved Remotes", AppState::SavedRemotes, true}
};

const int remotesMenuTotalItems = sizeof(remotesMenu) / sizeof(remotesMenu[0]);


void renderRemotesMenuView() {
  startFrame();

  if (changeView(AppState::MainMenu, KEY_ESC)) {
    endFrame();
    menuRedraw = false;
    return;
  }

drawMenu(remotesMenu, remotesMenuTotalItems);
handleMenuInput(remotesMenu, remotesMenuTotalItems);

  endFrame();
  menuRedraw = false;
}





