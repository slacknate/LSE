#ifndef LSE_GL_WINDOW_H
#define LSE_GL_WINDOW_H

#if defined(_WIN32) || defined(_WIN64) // windows

#include "gui/window/win.h"

#elif defined(__unix__) && !defined(__APPLE__) // all unix variants, non-mac

#include "gui/window/nix.h"

#elif defined(__APPLE__) && !defined(__MACH__) // mac osx, non-ios

#include "gui/window/mac.h"

#endif

#endif
