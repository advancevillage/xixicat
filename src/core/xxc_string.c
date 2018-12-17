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