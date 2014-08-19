#ifndef LSE_TIME_H
#define LSE_TIME_H

namespace LSE {

extern const unsigned int TIME_STR_LENGTH;
extern const unsigned int DAY_DATE_STR_LENGTH;

void get_local_time(char *ptr);
void get_day_and_date(char *ptr);

}

#endif
