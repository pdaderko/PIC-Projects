#include <stdint.h>
#include <stdbool.h>
#include "add1024weeks.h"

inline uint8_t is_leap_year(uint8_t years_since_2000) {
    return (years_since_2000 & 0x3) ? 0 : 1; // works for 2000 <= year < 2100
}

void add_1024_weeks(uint8_t *year, uint8_t *month, uint8_t *day) {
    // year is years since 2000, month is 1-indexed, day is 1-indexed
    // note that 1024 weeks is 19 365-day years + 233 days (leap days adjusted later)
    // there are either 4 or 5 leap days in any set of 19 years (between 2000 and 2099)

    uint8_t i;
    const uint16_t cumul_days_in_month[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    uint16_t day_of_year;
    
    day_of_year = cumul_days_in_month[*month - 1] + *day;
    if (is_leap_year(*year) && *month >= 3) day_of_year++; // Add 1 for leap day if in March (1-index)

    // advance 19 years, keeping track of leap days passed
    *year += 19;
    day_of_year += 233 - 5 + is_leap_year(*year);
    
    // check if we've rolled over into new year
    if (day_of_year > 365 + is_leap_year(*year)) {
        day_of_year -= 365 + is_leap_year((*year)++);
    }
    
    // Temporarily remove extra day if leap day exists and past feb 28th
    //  this is relatively the same as increasing cumulative days in the table
    bool hide_extra_day = (is_leap_year(*year) && day_of_year > cumul_days_in_month[2]);
    if (hide_extra_day) day_of_year--;
    
    // Convert day of year to (month, day)
    *month = 0;
    while (day_of_year > cumul_days_in_month[++(*month)]) {
        // this loop left intentionally blank
    }
    day_of_year -= cumul_days_in_month[*month-1];
    
    // Add extra "hidden" day back in, if in the month of February (1-index)
    if (hide_extra_day && (*month)==2) day_of_year++;
    
    *day = day_of_year; // store day
    
    return;
}

