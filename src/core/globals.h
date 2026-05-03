#ifndef GLOBALS_H
#define GLOBALS_H

#include "app_state.h"
#include "definitions.h"

String getTitleByState(AppState state);


extern AppState currentState;
extern bool menuRedraw;
extern bool sdCardAvailable;
extern String keyboardInputData;
extern String selectedRemotePath;
extern String selectedRemoteName;

#endif