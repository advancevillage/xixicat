/**
 * Copyright (C) richard sun
 */
#ifndef _XXC_JSON_H_INCLUDED_
#define _XXC_JSON_H_INCLUDED_

#include <xxc_config.h>
#include <xxc_core.h>
#include <cJSON.h>

typedef     cJSON       xxc_json_t;

/**
 *@brief: 创建JSON对象
 *@retval: xxc_json_t*
 */
#define xxc_json_create_object()           cJSON_CreateObject()
/**
 *@brief: 创建JSON字符串数组
 *@param: const char **  strings
 *@param: int count
 *@retval: xxc_json_t*
 */
#define xxc_json_create_string_array(strings,count)      cJSON_CreateStringArray(strings, count);


#endif /* _XXC_JSON_H_INCLUDED_ */