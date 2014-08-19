#include <ctime>
#include "util/time.h"

namespace LSE {
    
const unsigned int TIME_STR_LENGTH = 8;
const unsigned int DAY_DATE_STR_LENGTH = 15;

/*
Get the local time as HH:MM:SS.
The piece of memory pointed to by ptr must
contain at least TIME_STR_LENGTH bytes.
*/
void get_local_time(char *ptr) {
    
    if(ptr != nullptr) {
        
        time_t raw_time;
        time(&raw_time);

        struct tm *time_info = localtime(&raw_time);
        strftime(ptr, TIME_STR_LENGTH, "%H:%M:%S", time_info);
    }
    else {
        
        // raise exception here
    }
}


/*

*/
void get_day_and_date(char *ptr) {
    
    if(ptr != nullptr) {
        
        time_t raw_time;
        time(&raw_time);

        struct tm *time_info = localtime(&raw_time);
        strftime(ptr, DAY_DATE_STR_LENGTH, "%a %b %d %G", time_info);
    }
    else {
        
        // raise exception here
    }
}

}
