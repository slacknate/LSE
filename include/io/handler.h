#ifndef LSE_IO_HANDLER_H
#define LSE_IO_HANDLER_H

#if defined(_WIN32) || defined(_WIN64) // windows

#include "io/win.h"

#elif defined(__unix__) && !defined(__APPLE__) // all unix variants, non-mac

#include "io/nix.h"

#elif defined(__APPLE__) && !defined(__MACH__) // mac osx, non-ios

#include "io/mac.h"

#endif

#endif
