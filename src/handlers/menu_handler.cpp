#include "menu_handler.h"
#include "../utils/input_utils.h"

static bool backHandled = false;


static void updateMenuScroll(int menuTotalItems) {
    if (menuSelectedIndex < topVisibleIndex) {
        topVisibleIndex = menuSelectedIndex;
    } else if (menuSelectedIndex >= topVisibleIndex + maxVisibleItems) {
        topVisibleIndex = menuSelectedIndex - maxVisibleItems + 1;
    }
}

void drawMenu(MenuItem items[], int menuTotalItems) {
    if (menuTotalItems <= 0) return;

    for (int i = 0; i < maxVisibleItems; i++) {
        int itemIndex = topVisibleIndex + i;
        if (itemIndex >= menuTotalItems) break;
        bool isSelected = (itemIndex == menuSelectedIndex);

        int yPos = bodyTextYPosition + (i * menuSpacing);
        Canvas.setCursor(bodyTextXPosition, yPos);

        if (!items[itemIndex].enabled) {
            Canvas.setTextColor(disabledTextColor, fillScreenColor);
            Canvas.printf("%s%s", isSelected ? "> " : "  ", items[itemIndex].label.c_str());
        } else {
            Canvas.setTextColor(itemIndex == menuSelectedIndex ? highlightedTextColor : headerTextColor, fillScreenColor);
            Canvas.printf("%s%s", itemIndex == menuSelectedIndex ? "> " : "  ", items[itemIndex].label.c_str());
        }
    }
}

void handleMenuInput(MenuItem menuItems[], int menuTotalItems) {
    if (menuTotalItems <= 0) return;
    if (!M5Cardputer.Keyboard.isChange()) return;

    if (isEnterPressed()) {
        if (!menuItems[menuSelectedIndex].enabled) {
            return;
        }

        if (currentState == AppState::ListSDCardRemotes ||
            currentState == AppState::ListLittleFSRemotes) {
            selectedRemoteName = menuItems[menuSelectedIndex].label;
            selectedRemotePath = "/ir/" + selectedRemoteName;
            Serial.printf("Selected file: %s\n", selectedRemotePath.c_str());
        }

        Serial.printf("ENTER: index=%d targetState=%d\n",
                  menuSelectedIndex,
                  (int)menuItems[menuSelectedIndex].targetState);

        currentState = menuItems[menuSelectedIndex].targetState;
        menuSelectedIndex = 0;
        topVisibleIndex = 0;
        menuRedraw = true;
        return;
    }

    int oldIndex = menuSelectedIndex;

    if (isUpPressed()) {
        menuSelectedIndex = (menuSelectedIndex - 1 + menuTotalItems) % menuTotalItems;
    } else if (isDownPressed()) {
        menuSelectedIndex = (menuSelectedIndex + 1) % menuTotalItems;
    }

    if (oldIndex != menuSelectedIndex) {
        updateMenuScroll(menuTotalItems);
        menuRedraw = true;
    }
}

bool changeView(AppState targetState, char inputKey) {
    if (isKeyPressed(inputKey)) {
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