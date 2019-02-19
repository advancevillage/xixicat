/*
 * Copyright (C) richard sun
 */

#ifndef _XXC_CONFIG_H_INCLUDED_
#define  _XXC_CONFIG_H_INCLUDED_

#include <xxc_linux_config.h>

#define xxc_cdecl
#define xxc_inline      inline

/**@breif: 为了保证平台的通用性 */
typedef intptr_t        xxc_int_t;
typedef uintptr_t       xxc_uint_t;


#define XXC_INT32_LEN   (sizeof("-2147483648") - 1)
#define XXC_INT64_LEN   (sizeof("-9223372036854775808") - 1)

#define  XXC_MAX_UINT32_VALUE  (uint32_t) 0xffffffff
#define  XXC_MAX_INT32_VALUE   (uint32_t) 0x7fffffff


#endif /* _XXC_CONFIG_H_INCLUDED_ */