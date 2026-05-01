#ifndef REMOTE_HANDLER_H
#define REMOTE_HANDLER_H



enum RemoteState {
  CREATE_REMOTE_CAPTURE_SIGNAL,
  CREATE_REMOTE_SAVE_BUTTON,
  CREATE_REMOTE_SAVE_BUTTON_CONFIRMED,
  CREATE_REMOTE_CHOOSE_NEXT_ACTION,
  CREATE_REMOTE_SAVE_REMOTE,
  CREATE_REMOTE_SAVE_LOCATION,
  CREATE_REMOTE_COMPLETE

};

#include "globals.h"
#include "display_utils.h"
#include "ir_handler.h"
#include "remote_states.h"


const char* remoteTitleByState(RemoteState state);
const uint8_t maxButtons = 16;
const uint8_t maxNameLen = 16;
const uint8_t maxPathLen = 96;
const uint8_t maxRemotes = 96;

struct RemoteButton {
  char name[maxNameLen];
  storedIrSignal signal;
  bool valid;
};

struct Remote {
  char name[maxNameLen];
  char filePath[maxPathLen];
  RemoteButton buttons[maxButtons];
  uint8_t buttonCount;
  bool valid;
};

extern Remote currentRemote;
extern RemoteButton currentRemoteButton;

void clearCurrentRemote();
void setCurrentRemoteName(const char* remoteName);
bool createRemoteButton(const char* buttonName, const storedIrSignal& signal);
void printIrFile(const char* filepath, fs::FS& fileLocation);
bool saveRemote(fs::FS& fileLocation);

#endif 