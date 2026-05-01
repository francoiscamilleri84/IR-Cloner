#include "menu_handler.h"

int menuSelectedIndex = 0;
int topVisibleIndex = 0;  
const int maxVisibleItems = 4;

void drawMenu(AppState state, MenuItem items[], int menuTotalItems) {
  for (int i = 0; i < maxVisibleItems; i++) {
    int itemIndex = topVisibleIndex + i;
    if (itemIndex >= menuTotalItems) break;

    int yPos = bodyTextYPosition + (i * menuSpacing);
    Canvas.setCursor(bodyTextXPosition, yPos);

    if (itemIndex == menuSelectedIndex) {
      Canvas.setTextColor(highlightedTextColor);
      Canvas.printf("> %s", items[itemIndex].label.c_str());
    } 
    else { 
      Canvas.setTextColor(headerTextColor);
      Canvas.printf("  %s", items[itemIndex].label.c_str());
    }
  }
}

void handleMenuInput(MenuItem menuItems[], int menuTotalItems) {
  if (!M5Cardputer.Keyboard.isChange()) return;
  if (!M5Cardputer.Keyboard.isPressed()) return;

  if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER)) {
    currentState = menuItems[menuSelectedIndex].targetState;
    menuSelectedIndex = 0;
    topVisibleIndex = 0;
    menuRedraw = true;
    return;
  }

  int oldIndex = menuSelectedIndex;

  if (M5Cardputer.Keyboard.isKeyPressed(KEY_UP)) {
    menuSelectedIndex = (menuSelectedIndex - 1 + menuTotalItems) % menuTotalItems;
  } else if (M5Cardputer.Keyboard.isKeyPressed(KEY_DOWN)) {
    menuSelectedIndex = (menuSelectedIndex + 1) % menuTotalItems;
  }

  if (oldIndex != menuSelectedIndex) {
    if (menuSelectedIndex < topVisibleIndex) {
      topVisibleIndex = menuSelectedIndex;
    } else if (menuSelectedIndex >= topVisibleIndex + maxVisibleItems) {
      topVisibleIndex = menuSelectedIndex - maxVisibleItems + 1;
    }
    menuRedraw = true;
  }
}
bool backHandled = false;

bool changeView(AppState targetState, char inputKey) {
  if (M5Cardputer.Keyboard.isKeyPressed(inputKey)) {
    if (!backHandled) {
      currentState = targetState;
      menuRedraw = true;
      backHandled = true;
      return true;
    }
  } else {
    backHandled = false;
  }
  return false;
}
