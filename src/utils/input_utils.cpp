#include "../utils/input_utils.h"
#include "../views/remotes.h"


bool handleKeyboardInput() {
    if (!isKeyEvent()) return false;

    auto status = M5Cardputer.Keyboard.keysState();

    if (status.del && !keyboardInputData.isEmpty()) {
        keyboardInputData.remove(keyboardInputData.length() - 1);
    }

    for (char c : status.word) {
        if (keyboardInputData.length() < maxNameLen) {
            keyboardInputData += c;
        }
    }

    return status.enter && !keyboardInputData.isEmpty();
}

bool isKeyEvent() {
    return M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed();
}

bool isEnterPressed() {
    return M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER);
}

bool isUpPressed() {
    return M5Cardputer.Keyboard.isKeyPressed(KEY_UP);
}

bool isDownPressed() {
    return M5Cardputer.Keyboard.isKeyPressed(KEY_DOWN);
}

bool isESCPressed() {
    return M5Cardputer.Keyboard.isKeyPressed(KEY_ESC);
}

bool isKeyPressed(char key) {
    return M5Cardputer.Keyboard.isKeyPressed(key);
}