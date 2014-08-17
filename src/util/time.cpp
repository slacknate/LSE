#include <ctime>
#include "util/time.h"

const unsigned int TIME_STR_LENGTH = 8;

namespace LSE {

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


void get_day_and_date(char *ptr) {
    
    if(ptr != nullptr) {
        
        // TODO: implement me!
    }
    else {
        
        // raise exception here
    }
}

}
