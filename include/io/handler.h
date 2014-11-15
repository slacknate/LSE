#ifndef LSE_IO_HANDLER_H
#define LSE_IO_HANDLER_H

#if WIN32 // windows

#include "io/win.h"

#elif UNIX // all unix variants, non-mac

#include "io/nix.h"

#elif APPLE // mac osx

#include "io/mac.h"

#else

#warning NO PLATFORM DETECTED

#endif

#endif
