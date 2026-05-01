#include <algorithm>
#include "M5Cardputer.h"
#include "display_utils.h"
#include "menu_handler.h"

static const int screenWidth = 240;
static const int screenHeight = 135;

M5Canvas Canvas(&M5Cardputer.Display); 

void initDisplay() {
    Canvas.createSprite(screenWidth, screenHeight);
}

void createDisp() {
    Canvas.setTextSize(bodyFontSize);
    Canvas.setTextColor(bodyTextColor);
    Canvas.setCursor(bodyTextMarginLeft, bodyTextMarginTop);
}

void startFrame() {
    Canvas.setTextDatum(top_left);
    Canvas.fillSprite(fillScreenColor);
    Canvas.fillSprite(fillScreenColor); 
    Canvas.setTextSize(headerFontSize);
    Canvas.setTextColor(headerTextColor);
    Canvas.setCursor(headerTextXPosition, headerTextYPosition);
    Canvas.println(getTitleByState(currentState));
    Canvas.drawFastHLine(0, 25, 240, headerTextColor);
}


void remoteFrame(RemoteState state) {
  Canvas.fillSprite(fillScreenColor);
  Canvas.setTextSize(headerFontSize);
  Canvas.setTextColor(headerTextColor);
  Canvas.setCursor(headerTextXPosition, headerTextYPosition);
  Canvas.println(remoteTitleByState(state));
  Canvas.drawFastHLine(0, 25, 240, headerTextColor);
}

void endFrame() {
    Canvas.pushSprite(0, 0);
}

void inputBox(int x, int y, int w, int h, const String& value) {
  Canvas.fillRect(x, y, w, h, fillScreenColor);
  Canvas.drawRect(x, y, w, h, bodyTextColor);
  Canvas.setTextColor(inputTextColor);
  Canvas.setTextSize(2);
  Canvas.setCursor(x + 5, y + 8);
  Canvas.print(value);
}

void drawOverlay(const char* overlayButtonText, const char* overlayText) {
  const int overlayX = 20;
  const int overlayY = 22;
  const int overlayW = 200;
  const int overlayH = 88;
  const int overlayR = 10;

  const int buttonW = 110;
  const int buttonH = 24;
  const int buttonX = (240 - buttonW) / 2;
  const int buttonY = overlayY + overlayH - 42;
  const int buttonR = 8;

  Canvas.fillSprite(overlayBgColor);

  Canvas.fillRoundRect(overlayX, overlayY, overlayW, overlayH, overlayR, fillScreenColor);
  Canvas.drawRoundRect(overlayX, overlayY, overlayW, overlayH, overlayR, overlayBorderColor);

  Canvas.setTextDatum(top_center);
  Canvas.setTextColor(headerTextColor, overlayBgColor);
  Canvas.drawString(overlayText, 120, overlayY + 20);

  Canvas.fillRoundRect(buttonX, buttonY, buttonW, buttonH, buttonR, buttonBgColor);
  Canvas.drawRoundRect(buttonX, buttonY, buttonW, buttonH, buttonR, overlayBorderColor);

  Canvas.setTextDatum(middle_center);
  Canvas.setTextColor(buttonTextColor, buttonBgColor);
  Canvas.drawString(overlayButtonText, 120, buttonY + buttonH / 2);
}



void runSplashView() {
    Canvas.fillScreen(fillScreenColor);

    for (int y = 0; y < splashHeight; ++y) {
        for (int x = 0; x < splashWidth; ++x) {
            uint16_t c = splashScreen[y * splashWidth + x];
            if (c == splashAlpha) continue;

            if (x < splashWidth && y < splashHeight) {
                Canvas.drawPixel(x - 1, y, c); 
            }
        }
    }
    Canvas.pushSprite(0, 0); 
    

}




