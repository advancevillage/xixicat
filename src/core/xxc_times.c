/**
 * Copyright (C) richard sun
 */
#include <xxc_config.h>
#include <xxc_core.h>

#define XXC_TIME_SLOTS   64

static xxc_uint_t    slot;
static u_char        log_iso8601[XXC_TIME_SLOTS][sizeof("1970-09-28T12:00:00+0600")];

static      xxc_time_t        cached_time[XXC_TIME_SLOTS];
volatile    xxc_time_t       *xxc_cached_time;
volatile    xxc_str_t         xxc_log_iso8601;

void xxc_time_init(void) {
    xxc_log_iso8601.len = sizeof("1970-09-28T12:00:00+0600") - 1;
    xxc_cached_time = &cached_time[0];
    xxc_time_update();
}

void xxc_time_update(void) {
    u_char          *p;
    xxc_tm_t         tm, gmt;
    time_t           sec;
    xxc_uint_t       msec;
    xxc_time_t      *tp;
    struct timeval   tv;

    xxc_gettimeofday(&tv);
    sec = tv.tv_sec;
    msec = tv.tv_usec / 1000;
    
    tp = &cached_time[slot];

    if (tp->sec == sec) {
        tp->msec = msec;
        //xxc_unlock(&xxc_time_lock);
        return;
    }

    if (slot == XXC_TIME_SLOTS - 1) {
        slot = 0;
    } else {
        slot++;
    }

    tp = &cached_time[slot];
    tp->sec = sec;
    tp->msec = msec;

    xxc_gmtime(sec, &gmt);

    p = &log_iso8601[slot][0];

    (void) xxc_sprintf(p, "%4d-%02d-%02dT%02d:%02d:%02d%c%02i%02i",
                       tm.xxc_tm_year, tm.xxc_tm_mon,
                       tm.xxc_tm_mday, tm.xxc_tm_hour,
                       tm.xxc_tm_min, tm.xxc_tm_sec,
                       tp->gmtoff < 0 ? '-' : '+',
                       xxc_abs(tp->gmtoff / 60), xxc_abs(tp->gmtoff % 60));
  
    xxc_log_iso8601.data = p;
}

void xxc_gmtime(time_t t, xxc_tm_t *tp) {
    xxc_int_t   yday;
    xxc_uint_t  n, sec, min, hour, mday, mon, year, wday, days, leap;
    /* the calculation is valid for positive time_t only */
    n = (xxc_uint_t) t;
    /* 86400 = 24 * 3600 */
    days = n / 86400;
    /* January 1, 1970 was Thursday */
    wday = (4 + days) % 7;
    n %= 86400;
    hour = n / 3600;
    n %= 3600;
    min = n / 60;
    sec = n % 60;
    /*
     * the algorithm based on Gauss' formula,
     * see src/http/xxc_http_parse_time.c
     */
    /* days since March 1, 1 BC */
    days = days - (31 + 28) + 719527;
    /*
     * The "days" should be adjusted to 1 only, however, some March 1st's go
     * to previous year, so we adjust them to 2.  This causes also shift of the
     * last February days to next year, but we catch the case when "yday"
     * becomes negative.
     */
    year = (days + 2) * 400 / (365 * 400 + 100 - 4 + 1);
    yday = days - (365 * year + year / 4 - year / 100 + year / 400);
    if (yday < 0) {
        leap = (year % 4 == 0) && (year % 100 || (year % 400 == 0));
        yday = 365 + leap + yday;
        year--;
    }
    /*
     * The empirical formula that maps "yday" to month.
     * There are at least 10 variants, some of them are:
     *     mon = (yday + 31) * 15 / 459
     *     mon = (yday + 31) * 17 / 520
     *     mon = (yday + 31) * 20 / 612
     */
    mon = (yday + 31) * 10 / 306;
    /* the Gauss' formula that evaluates days before the month */
    mday = yday - (367 * mon / 12 - 30) + 1;
    if (yday >= 306) {
        year++;
        mon -= 10;
    } else {
        mon += 2;
    }

    tp->xxc_tm_sec = (xxc_tm_sec_t) sec;
    tp->xxc_tm_min = (xxc_tm_min_t) min;
    tp->xxc_tm_hour = (xxc_tm_hour_t) hour;
    tp->xxc_tm_mday = (xxc_tm_mday_t) mday;
    tp->xxc_tm_mon = (xxc_tm_mon_t) mon;
    tp->xxc_tm_year = (xxc_tm_year_t) year;
    tp->xxc_tm_wday = (xxc_tm_wday_t) wday;
}