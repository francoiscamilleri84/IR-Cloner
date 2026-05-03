#ifndef MENU_HANDLER_H
#define MENU_HANDLER_H

#include <Arduino.h>
#include "../core/app_state.h"
#include "../core/definitions.h"
#include "../core/globals.h"
#include "../handlers/menu_state.h"
#include "../models/menu_item.h"
#include "../utils/display_utils.h"


void drawMenu(MenuItem items[], int menuTotalItems);
void handleMenuInput(MenuItem menuItems[], int menuTotalItems);
bool changeView(AppState targetState, char inputKey);

#endif