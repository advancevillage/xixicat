/**
 * Copyright (C) richard sun
 */
#include <xxc_config.h>
#include <xxc_core.h>
#include <xixicat.h>

int xxc_cdecl main(int argc, char* argv[]) {
    xxc_int_t  t = 12;
    printf("n = %ld\n", t);
    printf("xixicat's version is %s\n", xixicat_version);

    printf("t up is %c\n", xxc_toupper('t'));
    printf("T lower is %c\n", xxc_toupper('T'));
    xxc_str_t src = xxc_string("hello xixicat!");   
    u_char *dst = (u_char*)malloc(sizeof(u_char) * 20);
    printf("src data is %s\n len is %ld\n", src.data,src.len);
    xxc_strup(dst, src.data, src.len);
    printf("dst is %s\n", dst);

    //buf
    xxc_str_t richard = xxc_string("richard");
    xxc_str_t kelly = xxc_string("kelly");
    u_char buf[100];
    xxc_sprintf(buf, "%s love %s forever", richard, kelly);
    printf("%s\n", buf);
    return XXC_OK;
}