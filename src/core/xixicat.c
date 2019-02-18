/**
 * Copyright (C) richard sun
 */
#include <xxc_config.h>
#include <xxc_core.h>
#include <xixicat.h>

int xxc_cdecl main(int argc, char* argv[]) {
    xxc_int_t  t = 112;
    printf("n = %ld\n", t);
    printf("xixicat's version is %s\n", xixicat_version);

    printf("t up is %c\n", xxc_toupper('t'));
    printf("T lower is %c\n", xxc_toupper('T'));
    xxc_str_t src = xxc_string("hello xixicat!");   
    u_char *dst = (u_char*)malloc(sizeof(u_char) * 20);
    memset(dst, 0, 20);
    printf("src data is %s\n len is %ld\n", src.data,src.len);
    xxc_strup(dst, src.data, src.len);
    printf("dst is %s\n", dst);

    //buf
    xxc_str_t richard = xxc_string("richard");
    xxc_str_t kelly = xxc_string("kelly");
    u_char buf[100];
    xxc_sprintf(buf, "%V", &src);
    printf("%s\n", buf);
    xxc_sprintf(buf,"xxc_int_t is %i", t);
    printf("%s\n", buf);
    memset(buf, 0, sizeof(buf));
    double f = 100.0001;
    xxc_sprintf(buf,"f is %.4f", f);
    printf("%s\n", buf);
    xxc_sprintf(buf, "%*s",5,dst);
    printf("%s\n", buf);
    time_t sec = xxc_time(&richard);
    xxc_str_t   file = xxc_string("xixicat.log");
    xxc_log_t   *log;
    log = xxc_log_init(&file);
    return XXC_OK;
}