#include "term.h"

#if (defined(_WIN32) || defined(_WIN64)) && !defined(__MINGW32__)
#include <conio.h>
#else

#include <stdio.h>

#define clrscr() printf("\e[1;1H\e[2J")
#endif

void clear() {
    clrscr();
}