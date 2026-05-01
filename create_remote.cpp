#include "create_remote.h"

static RemoteState remoteState = CREATE_REMOTE_CAPTURE_SIGNAL;

static void resetCreateRemoteFlow() {
  remoteState = CREATE_REMOTE_CAPTURE_SIGNAL;
  resetCaptureState();
  keyboardInputData = "";
}

static void drawRemoteCapturedTextView() {
  Canvas.setCursor(bodyTextMarginLeft, bodyTextMarginTop + 55);
  Canvas.setTextColor(bodyTextColor);
  Canvas.setTextSize(bodyFontSize);
  Canvas.println("Press [Enter] to name button");
  Canvas.setCursor(bodyTextMarginLeft, bodyTextMarginTop + 75);
  Canvas.println("Press [G0] to recapture");
}

void runCreateRemoteView() {

  remoteFrame(remoteState);
  createDisp();

  if (M5Cardputer.Keyboard.isKeyPressed(KEY_BACK)) {
    resetCreateRemoteFlow();
    currentState = REMOTE_MODE;
    menuRedraw = true;
    return;
  }

  switch (remoteState) {
    case CREATE_REMOTE_CAPTURE_SIGNAL:
      processCapture();
      if (!isCaptured || !lastIrSignal.valid){
        drawCaptureWaitingView();
      } else {
        drawCapturedSignalView();
        drawRemoteCapturedTextView();
      }

      if (isCaptured &&
          M5Cardputer.Keyboard.isChange() &&
          M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER)) {
        remoteState = CREATE_REMOTE_SAVE_BUTTON;
      }

      if (isCaptured && M5Cardputer.BtnA.wasPressed()) {
        resetCaptureState();
      }
      break;

    case CREATE_REMOTE_SAVE_BUTTON:{
      Canvas.setCursor(bodyTextMarginLeft, bodyTextMarginTop);
      Canvas.println("Button name:");
      int inputY = Canvas.getCursorY() + 4;
      inputBox(bodyTextMarginLeft, inputY, 220, 30, keyboardInputData);
      handleKeyboardInput(remoteState, CREATE_REMOTE_SAVE_BUTTON_CONFIRMED);

      if (isCaptured && M5Cardputer.BtnA.wasPressed()) {
        resetCaptureState();
      }
      break;
    }

    case CREATE_REMOTE_SAVE_BUTTON_CONFIRMED:
      drawOverlay("Continue", "Button Saved");
      endFrame();
      if (M5Cardputer.Keyboard.isChange() &&
          M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER)) {
        remoteState = CREATE_REMOTE_CHOOSE_NEXT_ACTION;
        setCurrentRemoteName("tempRemoteName");
        createRemoteButton(keyboardInputData.c_str(),lastIrSignal);
        
      }
      break;
    
    case CREATE_REMOTE_CHOOSE_NEXT_ACTION:
      keyboardInputData = "";
      Canvas.setTextDatum(top_left);
      Canvas.setCursor(bodyTextMarginLeft, bodyTextMarginTop);
      Canvas.print("Press [Enter] to create new button");
      Canvas.setCursor(bodyTextMarginLeft, bodyTextMarginTop + 20);
      Canvas.print("Press [s] to save remote");
      if (M5Cardputer.Keyboard.isChange()){
        
        if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER)){
          resetCaptureState();
          remoteState = CREATE_REMOTE_CAPTURE_SIGNAL;
        }
        else if(M5Cardputer.Keyboard.isKeyPressed('s')) {
          remoteState = CREATE_REMOTE_SAVE_REMOTE;
        }
      }
      break;
    

    case CREATE_REMOTE_SAVE_REMOTE:{
      
      Canvas.setCursor(bodyTextMarginLeft, bodyTextMarginTop);
      Canvas.println("Remote name:");
      int inputY = Canvas.getCursorY() + 4;
      inputBox(bodyTextMarginLeft, inputY, 220, 30, keyboardInputData);
      handleKeyboardInput(remoteState, CREATE_REMOTE_SAVE_LOCATION);

      break;
    }

    case CREATE_REMOTE_SAVE_LOCATION:

      setCurrentRemoteName(keyboardInputData.c_str());
      Canvas.setCursor(bodyTextMarginLeft, bodyTextMarginTop);
      Canvas.print("[f] - LittleFS");
      Canvas.setCursor(bodyTextMarginLeft, bodyTextMarginTop + 20);
      Canvas.print("[s] - SD Card");
      if (M5Cardputer.Keyboard.isChange()){
        
        if (M5Cardputer.Keyboard.isKeyPressed('f')){

          saveRemote(LittleFS);
          remoteState = CREATE_REMOTE_COMPLETE;
          
        }
        else if(M5Cardputer.Keyboard.isKeyPressed('s')) {

          saveRemote(SD);
          remoteState = CREATE_REMOTE_COMPLETE;

        }
      }
     
      break;

    case CREATE_REMOTE_COMPLETE:
      drawOverlay("Continue", "Remote Saved");
      endFrame();

      if (M5Cardputer.Keyboard.isChange() &&
          M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER)) {
          resetCaptureState();
          menuRedraw = true;
          currentState = REMOTE_MODE;
          
          
          return;
      }
      break;
  }

  endFrame();
}

