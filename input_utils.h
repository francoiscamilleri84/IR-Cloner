#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include "M5Cardputer.h"
#include "globals.h"
#include "remotes.h"
#include "remote_handler.h"
#include "saved_remotes.h"


extern String keyboardInputData;

void inputBox(int x, int y, int w, int h, const String& value);
bool handleKeyboardInput(RemoteState& currentState, RemoteState nextState);

#endif
