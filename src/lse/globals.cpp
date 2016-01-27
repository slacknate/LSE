#include "lse/globals.h"

namespace LSE {

/*
System logger.
*/
Logger logger(LOG_LEVEL_DEBUG);

/*
Viewing and projection matrices.
They are column major format:

0 4 8  12
1 5 9  13
2 6 10 14
3 7 11 15
*/
float VIEW_MATRIX[16], PROJ_MATRIX[16];

}
