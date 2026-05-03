#include "sound_utils.h"

void generateReceivedTone() {
  M5Cardputer.Speaker.tone(2000, 100);
  delay(250);
}

void generateSendTone() {
  M5Cardputer.Speaker.tone(1000, 100);
  delay(250);
}