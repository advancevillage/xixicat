/**
 * Copyright (C) richard sun
 */
#ifndef _XXC_CORE_H_INCLUDED_
#define _XXC_CORE_H_INCLUDED_

#include <xxc_config.h>

#define XXC_OK          0   
#define XXC_ERROR      -1

#include <xxc_string.h>
#include <xxc_times.h>

/**
 *@brief: 数值基本处理算法
 */
#define xxc_abs(value)       (((value) >= 0) ? (value) : - (value))
#define xxc_max(val1, val2)  ((val1 < val2) ? (val2) : (val1))
#define xxc_min(val1, val2)  ((val1 > val2) ? (val2) : (val1))

#endif /* _XXC_CORE_H_INCLUDED_ */