#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void)
{
    time_t epoch = 0;
    struct tm local;

    tzset();
    if (!localtime_r(&epoch, &local)) {
        perror("localtime_r");
        return 1;
    }
    if (local.tm_hour != 8 || local.tm_gmtoff != 28800) {
        fprintf(stderr, "unexpected local time: hour=%d offset=%d\n",
                local.tm_hour, local.tm_gmtoff);
        return 2;
    }
    if (timezone != -28800 || daylight != 0 || strcmp(tzname[0], "CST")) {
        fprintf(stderr, "unexpected timezone globals: timezone=%ld daylight=%d tzname=%s\n",
                timezone, daylight, tzname[0]);
        return 3;
    }
    printf("TZ=%s local=%04d-%02d-%02d %02d:%02d:%02d offset=%d zone=%s\n",
           getenv("TZ"), local.tm_year + 1900, local.tm_mon + 1, local.tm_mday,
           local.tm_hour, local.tm_min, local.tm_sec, local.tm_gmtoff,
           local.tm_zone);
    return 0;
}
