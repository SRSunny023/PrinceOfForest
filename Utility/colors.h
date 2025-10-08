#ifndef COLORS_H
#define COLORS_H

#include "utility.h"

// Foreground colors
inline const char* GREEN()  { return COLOR_ENABLED ? "\033[1;32m" : ""; }
inline const char* RED()    { return COLOR_ENABLED ? "\033[1;31m" : ""; }
inline const char* CYAN()   { return COLOR_ENABLED ? "\033[1;36m" : ""; }
inline const char* YELLOW() { return COLOR_ENABLED ? "\033[1;33m" : ""; }
inline const char* BLUE()   { return COLOR_ENABLED ? "\033[1;34m" : ""; }
inline const char* WHITE()  { return COLOR_ENABLED ? "\033[1;37m" : ""; }

// Background colors
inline const char* BGGREEN()  { return COLOR_ENABLED ? "\033[42m" : ""; }
inline const char* BGRED()    { return COLOR_ENABLED ? "\033[41m" : ""; }
inline const char* BGCYAN()   { return COLOR_ENABLED ? "\033[46m" : ""; }
inline const char* BGYELLOW() { return COLOR_ENABLED ? "\033[43m" : ""; }
inline const char* BGBLUE()   { return COLOR_ENABLED ? "\033[44m" : ""; }
inline const char* BGWHITE()  { return COLOR_ENABLED ? "\033[47m" : ""; }

// Reset
inline const char* RESET()    { return COLOR_ENABLED ? "\033[0m" : ""; }

#endif
