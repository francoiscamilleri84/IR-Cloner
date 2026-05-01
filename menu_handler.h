#ifndef MENU_HANDLER_H
#define MENU_HANDLER_H

#include "globals.h"
#include "display_utils.h"

extern bool menuRedraw;
extern int menuSelectedIndex;
extern int topVisibleIndex;

void drawMenu(AppState state, MenuItem items[], int menuTotalItems);
void handleMenuInput(MenuItem menuItems[], int menuTotalItems);
bool changeView(AppState targetState, char inputKey);

#endif