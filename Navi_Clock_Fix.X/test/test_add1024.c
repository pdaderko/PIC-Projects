#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include "add1024weeks.h"

void test_with_mktime(uint8_t *year, uint8_t *month, uint8_t *day) {
    struct tm *date;
    time_t conv_date = 0;
    
    date = gmtime(&conv_date);
    date->tm_year = *year + 100;
    date->tm_mon = *month - 1;
    date->tm_mday = *day;
    
    conv_date = mktime(date);
    conv_date += ((uint32_t)1024*7*24*60*60); // 1024 weeks in seconds
    date = gmtime(&conv_date);
    
    *year = date->tm_year - 100;
    *month = date->tm_mon + 1;
    *day = date->tm_mday;
    
    return;
}

int main(int argc, char* argv[]) {
    uint8_t orig_year;  // years since 2000
    uint8_t orig_month; // 1-indexed month
    uint8_t orig_day;   // 1-indexed day
    uint8_t year_mk, month_mk, day_mk;
    uint8_t year_add, month_add, day_add;
    const uint8_t days_in_month[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    bool errors = false;

    for (orig_year = 0; orig_year < 80; orig_year++) {
        for (orig_month = 1; orig_month < 13; orig_month++) {
            for (orig_day = 1; orig_day < days_in_month[orig_month] + is_leap_year(orig_year); orig_day++) {
                
                year_mk = orig_year;  month_mk = orig_month;  day_mk = orig_day;
                test_with_mktime(&year_mk, &month_mk, &day_mk);

                year_add = orig_year;  month_add = orig_month;  day_add = orig_day;
                add_1024_weeks(&year_add, &month_add, &day_add);

                if ((year_mk != year_add || month_mk != month_add || day_mk != day_add)) {
                    printf("Original  Year=%" PRIu16 "  Month=%" PRIu8 "  Day=%" PRIu8 "\n", ((uint16_t)orig_year + 2000), orig_month, orig_day);
                    printf("mktime    Year=%" PRIu16 "  Month=%" PRIu8 "  Day=%" PRIu8 "\n", ((uint16_t)year_mk + 2000), month_mk, day_mk);
                    printf("add1024   Year=%" PRIu16 "  Month=%" PRIu8 "  Day=%" PRIu8 "\n", ((uint16_t)year_add + 2000), month_add, day_add);
                    printf("\n");
                    errors = true;
                }
            }
        }
    }
    
    return (errors) ? 1 : 0;
    
}

