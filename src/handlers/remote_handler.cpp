#include "remote_handler.h"
#include <string.h>

Remote currentRemote = {};
RemoteButton currentRemoteButton{};

void clearCurrentRemote() {
  memset(&currentRemote, 0, sizeof(currentRemote));
  memset(&currentRemoteButton, 0, sizeof(currentRemoteButton));
  Serial.println("clearCurrentRemote: remote state reset");
}

void setCurrentRemoteName(const char* remoteName) {
  strncpy(currentRemote.name, remoteName, sizeof(currentRemote.name) - 1);
  currentRemote.name[sizeof(currentRemote.name) - 1] = '\0';
}

bool createRemoteButton(const char* buttonName, const storedIrSignal& signal) {
  if (!buttonName || buttonName[0] == '\0') {
    return false;
  }

  if (currentRemote.buttonCount >= maxButtons) {
    return false;
  }

  int index = currentRemote.buttonCount;
  strncpy(currentRemote.buttons[index].name, buttonName, sizeof(currentRemote.buttons[index].name) - 1);
  currentRemote.buttons[index].name[sizeof(currentRemote.buttons[index].name) - 1] = '\0';
  currentRemote.buttons[index].signal = signal;
  currentRemote.buttons[index].valid = true;
  currentRemote.buttonCount++;
  currentRemote.valid = true;
  return true;
}

bool saveRemote(fs::FS& fileLocation) {
  if (currentRemote.name[0] == '\0') {
    Serial.println("saveRemote: remote name is empty");
    return false;
  }

  if (currentRemote.buttonCount == 0) {
    Serial.println("saveRemote: no buttons to save");
    return false;
  }

  char cleanRemoteName[maxNameLen];
  cleanFilename(cleanRemoteName, currentRemote.name, sizeof(cleanRemoteName));

  snprintf(currentRemote.filePath,
           sizeof(currentRemote.filePath),
           "/ir/%s.ir",
           cleanRemoteName);

  if (!ensureIrDirectory(fileLocation)) {
    return false;
  }

  Serial.printf("Saving to: %s\n", currentRemote.filePath);

  if (fileLocation.exists(currentRemote.filePath)) {
    fileLocation.remove(currentRemote.filePath);
    Serial.printf("Cleared existing %s\n", currentRemote.filePath);
  }

  File file = fileLocation.open(currentRemote.filePath, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return false;
  }

  file.println("Filetype: IR signals file");
  file.println("Version: 1");
  file.println("#");
  file.printf("remote: %s\n", currentRemote.name);
  file.printf("buttoncount: %u\n", currentRemote.buttonCount);

  for (int i = 0; i < currentRemote.buttonCount; i++) {
    file.println("#");
    file.printf("name: %s\n", currentRemote.buttons[i].name);
    file.printf("protocol: %d\n", currentRemote.buttons[i].signal.protocol);
    file.printf("address: %u\n", currentRemote.buttons[i].signal.address);
    file.printf("command: %u\n", currentRemote.buttons[i].signal.command);
  }

  file.close();
  Serial.println("Remote saved successfully!");
  printIrFile(fileLocation, currentRemote.filePath);
  clearCurrentRemote();
  return true;
}