#include "splash.h"

#include "../core/globals.h"
#include "../utils/display_utils.h"
#include "../core/splash_sprite.h"
#include <M5Cardputer.h>

static void handleSplashInput();
static void drawSplashView();

void renderSplashView() {
    handleSplashInput();
    if (currentState != AppState::Splash) return;
    drawSplashView();
}

static void handleSplashInput() {
    if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
        currentState = AppState::MainMenu;
        menuRedraw = true;
    }
}

static void drawSplashView() {
    Canvas.fillScreen(fillScreenColor);

    for (int y = 0; y < splashHeight; ++y) {
        for (int x = 0; x < splashWidth; ++x) {
            uint16_t color = splashScreen[y * splashWidth + x];
            if (color == splashAlpha) continue;

            Canvas.drawPixel(x, y, color);
        }
    }

    Canvas.pushSprite(0, 0);
}