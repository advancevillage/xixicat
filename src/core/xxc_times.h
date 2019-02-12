/**
 * Copyright (C) richard sun
 */
#ifndef _XXC_TIMES_H_INCLUDED_
#define  _XXC_TIMES_H_INCLUDED_

#include <xxc_config.h>
#include <xxc_core.h>

typedef struct xxc_time_s xxc_time_t;

struct xxc_time_s {
    /* 格林威治时间1970年1月1日凌晨0点0分0秒到当前时间的秒数 */
    time_t      sec;
    /* sec成员只能精确到秒，msec则是当前时间相对于sec的毫秒偏移量 */
    xxc_uint_t  msec;
    /* 时区 */
    xxc_int_t   gmtoff;
};
/**
 *@brief: 获取当前GMT时间
 *@param: t 当前时间字符串
 *@retval: 时间戳
 */
time_t xxc_time(xxc_str_t  *t);

/**
 *@breif:  时间转换
 *@param:  t  sec
 *@param:  tp 
 */
void xxc_gmtime(time_t t, xxc_tm_t *tp);

/**
 *@brief: 获取当前时间
 */

#endif /* _XXC_TIMES_H_INCLUDED_ */