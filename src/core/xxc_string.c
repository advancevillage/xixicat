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
 *    %[0][width][u][x|X]z         ssize_t/size_t
 *    %[0][width][u][x|X]d         int/u_int
 *    %[0][width][u][x|X]l         long
 *    %[0][width][u][x|X]i         xxc_int_t/xxc_uint_t
 *    %[0][width][u][x|X]D         int32_t/uint32_t
 *    %[0][width][u][x|X]L         int64_t/uint64_t
 *    %[0][width][.width]f         double
 *    %[0][width]T                 time_t
 *    %M                           xxc_msec_t
 *    %p                           void*
 *    %V                           xxc_str_t*
 *    %s                           null-terminated string
 *    %*s                          length and string
 *    %Z                           '\0'
 *    %N                           '\n'
 *    %c                           char
 *    %%                            %
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

u_char* xxc_vslprintf(u_char *buf, u_char *last, const char *fmt, va_list args){
    u_char      *p, zero;
    int          d;
    double       f;
    int64_t      i64;
    uint64_t     ui64;
    size_t       len, slen;
    xxc_int_t    width, frac_width, hex, sign;
    while(*fmt && buf < last){
        /**
         *@brief: 字符串处理-格式化处理 如果碰到'%'进行处理
         *        处理逻辑要支持 以上格式
         *        1: 判断填充方式
         *        2: 判断宽度
         */
        if(*fmt == '%'){
            i64 = 0;
            ui64 = 0;
            zero = (u_char)((*++fmt == '0') ? '0' : ' ');
            /**
             *@param: width         填充宽度,默认是0
             *@param: frac_width    精度宽度,默认是0
             *@param; hex  1 = 'x'  2 = 'X'
             *@parma: sign          符号标志位,默认是有符号
             *@parma: slen          设定字符串宽度
             */
            width = 0;
            frac_width = 0;
            sign = 1;
            while(*fmt >= '0' && *fmt <= '9'){
                width = width * 10 + *fmt++ - '0';
            }
            /**
             *@brief: 处理修饰符
             */
            for( ;; ){
                switch(*fmt){
                    case 'u':
                        sign = 0;
                        fmt++;
                        continue;
                    case 'x':
                        sign = 0;
                        hex = 1;
                        fmt++;
                        continue;
                    case 'X':
                        sign = 0;
                        hex = 2;
                        fmt++;
                        continue;
                    case '.':
                        fmt++;
                        while (*fmt >= '0' && *fmt <= '9') {
                            frac_width = frac_width * 10 + *fmt++ - '0';
                        }
                        break;
                    case '*':
                        slen = va_arg(args, size_t);
                        fmt++;
                        continue;
                    default:
                        break;
                }
                break;
            }

            switch(*fmt){
                case 'z':
                case 'd':
                case 'l':
                case 'i':
                case 'D':
                case 'L':
                case 'f':
                case 'T':
                case 'M':
                case 'p':
                case 'V':
                case 's':
                case 'Z':
                case 'N':
                case 'c':
                case '%':
                default:
                    *buf++ = *fmt++;
            }
        }else{
            *buf++ = *fmt++;
        }
    }
    return buf;
}