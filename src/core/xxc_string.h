/**
 * Copyright (C) richard sun
 */
#ifndef _XXC_STRING_H_INCLUDED_
#define _XXC_STRING_H_INCLUDED_

#include <xxc_config.h>
#include <xxc_core.h>

typedef struct xxc_str_s            xxc_str_t;

/**
 *@brief: 字符串结构体 xxc_str_s
 *@param: len 字符串长度
 *@param: *data 数据指针
 */
struct xxc_str_s {
    size_t      len;
    u_char    *data;
};

#define xxc_string(str)         {sizeof(str)-1, (u_char*)str}
#define xxc_null_string         {0, NULL}

#define xxc_tolower(c)      (u_char) ((c >= 'A' && c <= 'Z') ? (c | 0x20) : c)
#define xxc_toupper(c)      (u_char) ((c >= 'a' && c <= 'z') ? (c & ~0x20) : c)

/**
 *@brief: 将字符串前n个字符转成小写字母
 *@param: dst 存储结果字符串
 *@param: src 源字符串
 *@param: n
 */
void xxc_strlow(u_char *dst, u_char *src, size_t n);

/**
 *@brief: 将字符串前n个字符转成大写字母
 *@param: dst 存储结果字符串
 *@param: src 源字符串
 *@param: n
 */
void xxc_strup(u_char *dst, u_char *src, size_t n);

/**
 *@brief: 将格式化字符串转储到字符串中
 *@param: buf 字符串指针
 *@param: fmt 格式化
 *@param: ... 参数集
 */
u_char* xxc_cdecl xxc_sprintf(u_char *buf, const char *fmt, ...);

u_char* xxc_vslprintf(u_char *buf, u_char *last, const char *fmt, va_list args);

#endif /* _XXC_STRING_H_INCLUDED_ */