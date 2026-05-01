#ifndef DISPLAY_UTILS_H
#define DISPLAY_UTILS_H

#include "globals.h"
#include "remote_handler.h"
#include "splash_sprite.h"
#include <M5GFX.h>

extern M5Canvas Canvas;
void initDisplay();
void startFrame();
void endFrame();
void createDisp();
void runSplashView();
void inputBox(int x, int y, int w, int h, const String& value);
void drawOverlay(const char* overlayButtonText, const char* overlayText);
void runButtonSavedOverlay(String OverlayButtonText, String overlayText);
void remoteFrame(RemoteState state);
bool changeView(AppState targetState, char inputKey);




#endif