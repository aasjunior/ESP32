#ifndef LITTLE_F_S_MANAGER_H
#define LITTLE_F_S_MANAGER_H

#include <LittleFS.h>

class LittleFSManager{
public:
    static bool mount();
    static bool format();
};

#endif // LITTLE_F_S_MANAGER_H