#include "FS.h"

class DynStorage {
   public:
    DynStorage();
    void begin();
    void end();
    void listFiles();
    uint64_t freeSpace();

   private:
    bool isInited;
};

extern SemaphoreHandle_t fsMutex;
extern DynStorage Storage;
extern fs::FS *contentFS;
extern void copyFile(File in, File out);
