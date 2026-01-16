#include "storage.h"

#include "LittleFS.h"

DynStorage::DynStorage() : isInited(0) {}

SemaphoreHandle_t fsMutex = NULL;

static void initLittleFS() {
    LittleFS.begin();
    contentFS = &LittleFS;
}

uint64_t DynStorage::freeSpace(){
    this->begin();
    return LittleFS.totalBytes() - LittleFS.usedBytes();
}

void copyFile(File in, File out) {
    Serial.print("Copying ");
    Serial.print(in.path());
    Serial.print(" to ");
    Serial.println(out.path());

    size_t n;
    uint8_t buf[64];
    while ((n = in.read(buf, sizeof(buf))) > 0) {
        out.write(buf, n);
    }
}

void DynStorage::begin() {
    if(fsMutex == NULL) {
        fsMutex = xSemaphoreCreateMutex();
    }
    initLittleFS();
    if (!contentFS->exists("/current")) {
        contentFS->mkdir("/current");
    }
    if (!contentFS->exists("/temp")) {
        contentFS->mkdir("/temp");
    }
}

void DynStorage::end() {
}

fs::FS* contentFS;
DynStorage Storage;
