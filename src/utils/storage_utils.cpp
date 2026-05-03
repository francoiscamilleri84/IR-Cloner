#include "storage_utils.h"

StorageType selectedStorage = STORAGE_NONE;

bool irDirectoryExists(fs::FS& fs) {
    return fs.exists("/ir");
}

bool ensureIrDirectory(fs::FS& fs) {
    if (irDirectoryExists(fs)) {
        return true;
    }

    Serial.println("Creating /ir directory...");
    if (!fs.mkdir("/ir")) {
        Serial.println("Failed to create /ir directory");
        return false;
    }

    Serial.println("/ir directory created");
    return true;
}

void printIrFile(fs::FS& fs, const char* filepath) {
    File file = fs.open(filepath, FILE_READ);
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

bool deleteIrFile(fs::FS& fs, const char* filepath) {
    if (!fs.exists(filepath)) {
        Serial.printf("deleteIrFile: file does not exist: %s\n", filepath);
        return false;
    }

    if (!fs.remove(filepath)) {
        Serial.printf("deleteIrFile: failed to delete %s\n", filepath);
        return false;
    }

    Serial.printf("deleteIrFile: deleted %s\n", filepath);
    return true;
}

void cleanFilename(char* dest, const char* src, size_t destSize) {
    if (!dest || destSize == 0) {
        return;
    }

    dest[0] = '\0';

    if (!src) {
        return;
    }

    strncpy(dest, src, destSize - 1);
    dest[destSize - 1] = '\0';

    for (size_t i = 0; dest[i] != '\0'; i++) {
        if (dest[i] == '/' || dest[i] == '\\' || dest[i] == ' ') {
            dest[i] = '_';
        }
    }
}
