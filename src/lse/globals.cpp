#include "lse/globals.h"

/*
Global viewing and projection matrices.
They are column major format:

0 4 8  12
1 5 9  13
2 6 10 14
3 7 11 15
*/
float LSE_VIEW_MATRIX[16], LSE_PROJ_MATRIX[16];