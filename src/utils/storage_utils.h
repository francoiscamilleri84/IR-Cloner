#pragma once

#include <Arduino.h>
#include <FS.h>
#include <stddef.h>
#include <string.h>

enum StorageType {
    STORAGE_NONE,
    STORAGE_LITTLEFS,
    STORAGE_SD
};

extern StorageType selectedStorage;

bool irDirectoryExists(fs::FS& fs);
bool ensureIrDirectory(fs::FS& fs);
void printIrFile(fs::FS& fs, const char* filepath);
bool deleteIrFile(fs::FS& fs, const char* filepath);
void cleanFilename(char* dest, const char* src, size_t destSize);