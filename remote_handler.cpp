#include "remote_handler.h"
#include <string.h>
#include <LittleFS.h>
#include <SD.h>
#include <FS.h>
#include <SPI.h>

Remote currentRemote = {};
RemoteButton currentRemoteButton{};

const char* remoteTitleByState(RemoteState state) {
  switch (state) {
    case CREATE_REMOTE_CAPTURE_SIGNAL:     return "CAPTURE SIGNAL";
    case CREATE_REMOTE_SAVE_BUTTON:        return "SAVE BUTTON";
    case CREATE_REMOTE_CHOOSE_NEXT_ACTION: return "NEXT ACTION";
    case CREATE_REMOTE_SAVE_REMOTE:        return "SAVE REMOTE";
    case CREATE_REMOTE_SAVE_LOCATION:      return "SAVE LOCATION";
    case CREATE_REMOTE_COMPLETE:           return "SAVED!";
    case LIST_LITTLE_FS_REMOTES:           return "Little FS";
    case LIST_SD_CARD_REMOTES:             return "SD Card";
    default:                               return "CARDPUTER:~/IR_TOOL";
  }
}

void clearCurrentRemote() {
  memset(&currentRemote, 0, sizeof(currentRemote));
  memset(&currentRemoteButton, 0, sizeof(currentRemoteButton));
  Serial.println("clearCurrentRemote: remote state reset");
}

void printIrFile(const char* filepath, fs::FS& fileLocation) {
  File file = fileLocation.open(filepath, FILE_READ);
  if (!file) {
    Serial.printf("printIrFile: failed to open %s\n", filepath);
    return;
  }

  Serial.printf("\n=== CONTENTS OF %s ===\n", filepath);

  while (file.available()) {
    String line = file.readStringUntil('\n');
    Serial.println(line);
  }

  Serial.println("=== END OF FILE ===\n");
  file.close();
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
  } else {
    int index = currentRemote.buttonCount;
    strncpy(currentRemote.buttons[index].name, buttonName, sizeof(currentRemote.buttons[index].name) - 1);
    currentRemote.buttons[index].name[sizeof(currentRemote.buttons[index].name) - 1] = '\0';
    currentRemote.buttons[index].signal = signal;
    currentRemote.buttonCount++;
    return true;
  }
}

bool saveRemote(fs::FS& fileLocation){
  if (currentRemote.name[0] == '\0') {
    Serial.println("saveRemote: remote name is empty");
    return true;
  }

  if (currentRemote.buttonCount == 0) {
    Serial.println("saveRemote: no buttons to save");
    return true;
  }

  String cleanRemoteName = String(currentRemote.name);
  cleanRemoteName.replace("/", "_");
  cleanRemoteName.replace("\\", "_");
  cleanRemoteName.replace(" ", "_");

  snprintf(currentRemote.filePath,
  sizeof(currentRemote.filePath),
  "/ir/%s.ir",
  cleanRemoteName.c_str());

  if (!fileLocation.exists("/ir")) {
    Serial.println("Creating /ir directory...");
    if (!fileLocation.mkdir("/ir")) {
      Serial.println("Failed to create /ir directory");
      return true;
    }
    Serial.println("/ir directory created");
  }

  Serial.printf("Saving to: %s\n", currentRemote.filePath);
  if (fileLocation.exists(currentRemote.filePath)) {
    fileLocation.remove(currentRemote.filePath);
    Serial.printf("Cleared existing %s\n", currentRemote.filePath);
  }
  File file = fileLocation.open(currentRemote.filePath, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return true;
  }

  file.println("Filetype: IR signals file");
  file.println("Version: 1");
  file.println("#");
  file.printf("remote: %s\n", currentRemote.name);
  Serial.printf("buttoncount: %u\n", currentRemote.buttonCount);
  for (int i = 0; i < currentRemote.buttonCount; i++) {
    file.println("#");
    file.printf("name: %s\n", currentRemote.buttons[i].name);
    file.printf("protocol: %d\n", currentRemote.buttons[i].signal.protocol);
    file.printf("address: %u\n", currentRemote.buttons[i].signal.address);
    file.printf("command: %u\n", currentRemote.buttons[i].signal.command);
  }

  file.close();

  Serial.println("Remote saved successfully!");
  printIrFile(currentRemote.filePath, fileLocation);
  clearCurrentRemote();
  return true;

  Serial.printf("saveRemote: unsupported file location: %s\n", currentRemote.filePath);
  
}


