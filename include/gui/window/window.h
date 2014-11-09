#ifndef LSE_GL_WINDOW_H
#define LSE_GL_WINDOW_H

#if WIN32 // windows

#include "gui/window/win.h"

#elif UNIX // all unix variants, non-mac

#include "gui/window/nix.h"

#elif APPLE // mac osx

#include "gui/window/mac.h"

#else

#warning NO PLATFORM DETECTED

#endif

#endif
