#ifndef MENU_ITEM_H
#define MENU_ITEM_H

#include <Arduino.h>
#include "../core/app_state.h"

struct MenuItem {
    String label;
    AppState targetState;
    bool enabled;
};

#endif