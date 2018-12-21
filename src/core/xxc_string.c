/**
 * Copyright (C) richard sun
 */
#include <xxc_config.h>
#include <xxc_core.h>

void xxc_strlow(u_char *dst, u_char *src, size_t n){
    while (n){
        *dst = xxc_tolower(*src);
        dst++;
        src++;
        n--;
    }
}

void xxc_strup(u_char *dst, u_char *src, size_t n){
    while (n) {
        *dst = xxc_toupper(*src);
        dst++;
        src++;
        n--;
    }
}

/*
 * supported formats:
 * 
 * 
 */
/** (void*) -1 = 0xFFFFFFFF */
u_char* xxc_cdecl xxc_sprintf(u_char* buf, const char* fmt, ...){
    u_char      *p = NULL;
    va_list      args;
    va_start(args, fmt);
    p = xxc_vslprintf(buf, (void *)-1, fmt, args);
    va_end(args);
    return p;
}
// TO DO
u_char* xxc_vslprintf(u_char *buf, u_char *last, const char *fmt, va_list args){
    xxc_str_t  str = xxc_string("hello string!");
    sprintf((char*)buf,fmt, str.data, str.data);
    return buf;
}