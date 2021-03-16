#include <stdlib.h>
#include <string.h>

#include "hardware.h"

#if defined(_WIN32) || defined(_WIN64)
const char *os = "win";
#else
#ifdef __linux
const char* os = "nix";
#else
const char* os = "";
#endif
#endif

void printCpuInfo() {
    if (strcmp(os, "win") != 0) {
        system("cat /proc/cpuinfo | grep \"model name\" | head -1");
    } else {
        system("for /f \"usebackq skip=1 tokens=*\" %i in (`wmic cpu get name ^| findstr /r /v \"^$\"`) do @echo %i");
    }
}
