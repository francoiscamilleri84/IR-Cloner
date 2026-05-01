
#include "input_utils.h"

extern String keyboardInputData = "";
bool handleKeyboardInput(RemoteState& currentState, RemoteState nextState) {
  if (M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
    Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();

    for (auto c : status.word) {
      if (keyboardInputData.length() < (maxNameLen - 1)) {
        keyboardInputData += c;
      }
    }

    if (status.del && keyboardInputData.length() > 0) {
      keyboardInputData.remove(keyboardInputData.length() - 1);
    }

    if (status.enter && keyboardInputData.length() > 0 && lastIrSignal.valid) {
        currentState = nextState;
        return true;
    }
  }
  return false;
}