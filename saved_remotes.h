#ifndef SAVED_REMOTES_H
#define SAVED_REMOTES_H

#include "globals.h"
#include "FS.h"
#include "SD.h"

void runSavedRemotesView();
void listRemoteFiles(fs::FS &fileLocation);
void listSavedRemotesView();

#endif