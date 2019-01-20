/**
 * Copyright (C) richard sun
 */
#ifndef _XXC_TIMES_H_INCLUDED_
#define  _XXC_TIMES_H_INCLUDED_

#include <xxc_config.h>
#include <xxc_core.h>

typedef struct xxc_time_s xxc_time_t;

struct xxc_time_s {
    time_t      sec;
    xxc_uint_t  msec;
    xxc_int_t   gmtoff;
};

/**
 *@breif: 定义全局变量
 */
extern volatile xxc_str_t    xxc_log_iso8601;
extern volatile xxc_time_t  *xxc_cached_time;

/**
 *@breif: 时间初始化
 */
void xxc_time_init(void);

/**
 *@brief: 更新时间(核心)
 */
void xxc_time_update(void);

#endif /* _XXC_TIMES_H_INCLUDED_ */