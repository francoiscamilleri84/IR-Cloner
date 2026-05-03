#ifndef SAVED_REMOTES_H
#define SAVED_REMOTES_H

#include "../core/globals.h"
#include "../core/main.h"
#include "../handlers/menu_handler.h"
#include "../handlers/remote_handler.h"
#include "../views/remotes.h"
#include "../utils/display_utils.h"
#include "../utils/input_utils.h"
#include "../utils/storage_utils.h"



void renderSavedRemotesView();
void listRemoteFiles(fs::FS &fileLocation);
void listSavedRemotesView(fs::FS &fileLocation);

#endif