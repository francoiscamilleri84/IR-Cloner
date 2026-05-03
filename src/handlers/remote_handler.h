#ifndef REMOTE_HANDLER_H
#define REMOTE_HANDLER_H

#include "../core/globals.h"
#include "../models/ir_signal.h"
#include "../models/remote_state.h"
#include "../utils/display_utils.h"
#include "../utils/storage_utils.h"
#include <Arduino.h>
#include <FS.h>

constexpr uint8_t maxButtons = 16;
constexpr uint8_t maxNameLen = 32;
constexpr uint8_t maxPathLen = 128;
constexpr uint8_t maxRemotes = 128;

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
bool saveRemote(fs::FS& fileLocation);

#endif