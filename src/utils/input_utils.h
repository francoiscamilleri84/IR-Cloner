#pragma once

#include <M5Cardputer.h>
#include <string>
#include "../core/globals.h"
#include "../handlers/remote_handler.h"
#include "../models/remote_state.h"
#include "../views/remotes.h"


bool isKeyEvent();
bool isUpPressed();
bool isDownPressed();
bool isEnterPressed();
bool isESCPressed();
bool isKeyPressed(char inputKey);

void inputBox(int x, int y, int w, int h, const String& value);
bool handleKeyboardInput();
bool handleRemoteStateInput(RemoteState& currentState, RemoteState nextState);

