#ifndef REMOTE_STATE_H
#define REMOTE_STATE_H

enum class RemoteState {
    CaptureSignal,
    SaveButton,
    SaveButtonConfirmed,
    ChooseNextAction,
    SaveRemote,
    SaveLocation,
    Complete
};
const char* remoteTitleByState(RemoteState state);

#endif