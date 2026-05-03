#include "main.h"

#include "M5Cardputer.h"

MenuItem mainMenu[] = {
  {"Remotes", AppState::Remotes, true},
  {"Spam Mode", AppState::SpamSignals, false},
  {"Settings", AppState::Settings, true}
};

const int mainMenuTotalItems = sizeof(mainMenu) / sizeof(mainMenu[0]);

void renderMainMenuView() {
  startFrame();
  changeView(AppState::MainMenu, KEY_ESC);
  drawMenu(mainMenu, mainMenuTotalItems); 
  handleMenuInput(mainMenu, mainMenuTotalItems);
  endFrame();
  menuRedraw = false;
}
