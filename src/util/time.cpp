#include <ctime>
#include <cerrno>
#include <iostream>
#include "util/time.h"

namespace LSE {
    
const unsigned int TIME_STR_LENGTH = 9;
const unsigned int DAY_DATE_STR_LENGTH = 16;

/*
Get the local time as 'Hour:Minute:Second'.
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
Get the day and date as 'Weekday Month Day Year'.
The piece of memory pointed to by ptr must
contain at least DAY_DATE_STR_LENGTH bytes.
*/
void get_day_and_date(char *ptr) {
    
    if(ptr != nullptr) {
        
        time_t raw_time;
        time(&raw_time);

        struct tm *time_info = localtime(&raw_time);
        strftime(ptr, DAY_DATE_STR_LENGTH, "%a %b %d %Y", time_info);
    }
    else {
        
        // raise exception here
    }
}

}
