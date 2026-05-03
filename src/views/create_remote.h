#ifndef CREATE_REMOTE_H
#define CREATE_REMOTE_H

#include "../models/remote_state.h"


struct RemoteStateMenuItem {
    const char* label;
    RemoteState targetState;
    bool enabled;
};

void renderCreateRemoteView();
static void resetCreateRemoteFlow();
void renderSaveRemoteView();



#endif