/**
 * Copyright (C) richard sun
 */
#ifndef _XXC_TIME_H_INCLUDED_
#define  _XXC_TIME_H_INCLUDED_

typedef struct tm           xxc_tm_t;

#define xxc_tm_sec            tm_sec
#define xxc_tm_min            tm_min
#define xxc_tm_hour           tm_hour
#define xxc_tm_mday           tm_mday
#define xxc_tm_mon            tm_mon
#define xxc_tm_year           tm_year
#define xxc_tm_wday           tm_wday
#define xxc_tm_isdst          tm_isdst

#define xxc_tm_sec_t          int
#define xxc_tm_min_t          int
#define xxc_tm_hour_t         int
#define xxc_tm_mday_t         int
#define xxc_tm_mon_t          int
#define xxc_tm_year_t         int
#define xxc_tm_wday_t         int



#endif /* _XXC_TIME_H_INCLUDED_ */