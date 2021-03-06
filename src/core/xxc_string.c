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
    uint64_t     ui64, frac;
    size_t       len, slen;
    xxc_int_t    width, frac_width, hex, sign, scale, n;
    xxc_str_t   *v;
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
             *@param: frac_width    精度宽度,默认是0(浮点数)
             *@param; hex  0 = 10进制  1 = 'x'  2 = 'X' 
             *@parma: sign          符号标志位,默认是有符号
             *@parma: slen          设定字符串宽度
             */
            width = 0;
            frac_width = 0;
            sign = 1;
            hex = 0;
            slen = (size_t) -1;
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
                    if(sign){
                        i64 = (int64_t) va_arg(args, ssize_t);
                    }else{
                        ui64 = (uint64_t) va_arg(args, size_t);
                    }
                    break;
                case 'd':
                    if(sign){
                        i64 = (int64_t) va_arg(args, int);
                    }else{
                        ui64 = (uint64_t) va_arg(args, u_int);
                    }
                    break;
                case 'l':
                    if(sign){
                        i64 = (int64_t) va_arg(args, long);
                    }else{
                        ui64 = (uint64_t) va_arg(args, u_long);
                    }
                    break;
                case 'i':
                    if(sign){
                        i64 = (int64_t)va_arg(args, xxc_int_t);
                    }else{
                        ui64 = (uint64_t)va_arg(args, xxc_uint_t);
                    }
                    break;
                case 'D':
                    if(sign){
                        i64 = (int64_t) va_arg(args, int32_t);
                    }else{
                        ui64 = (uint64_t) va_arg(args, uint32_t);
                    }
                    break;
                case 'L':
                    if(sign){
                        i64 = va_arg(args, int64_t);
                    }else{
                        ui64 = va_arg(args, uint64_t);
                    }
                    break;
                case 'f':
                    f = va_arg(args, double);
                    if(f < 0){
                        *buf++ = '-';
                        f = -f;
                    }
                    ui64 = (int64_t) f;
                    frac = 0;
                    if (frac_width) {
                        scale = 1;
                        for (n = frac_width; n; n--) {
                            scale *= 10;
                        }
                        frac = (uint64_t) ((f - (double) ui64) * scale + 0.5);
                        if (frac == scale) {
                            ui64++;
                            frac = 0;
                        }
                    }
                    buf = xxc_sprintf_num(buf, last, ui64, zero, 0, width);
                    if (frac_width) {
                        if (buf < last) {
                            *buf++ = '.';
                        }
                        buf = xxc_sprintf_num(buf, last, frac, '0', 0, frac_width);
                    }
                    fmt++;
                    continue;
                case 'T':
                    i64 = (int64_t) va_arg(args, time_t);
                    sign = 1;
                    break;
                case 'M':
                case 'p':
                    ui64 = (uintptr_t) va_arg(args, void *);
                    hex = 2;
                    sign = 0;
                    zero = '0';
                    width = 2 * sizeof(void *);
                    break;
                case 'V':
                    v = va_arg(args, xxc_str_t *);
                    len = xxc_min((size_t)(last - buf), v->len);
                    buf = xxc_cpymem(buf, v->data, len);
                    fmt++;
                    continue;
                case 's':
                    p = va_arg(args, u_char *);
                    if (slen == (size_t) -1) {
                        while (*p && buf < last) {
                            *buf++ = *p++;
                        }
                    } else {
                        len = xxc_min(((size_t) (last - buf)), slen);
                        buf = xxc_cpymem(buf, p, len);
                    }
                    fmt++;  
                    continue;
                case 'Z':
                    *buf++ = '\0';
                    fmt++;
                    continue;
                case 'N':
                    *buf++ = LF;
                    fmt++;
                    continue;
                case 'c':
                    d = va_arg(args, int);
                    *buf++ = (u_char) (d & 0xff);
                    fmt++;
                    continue;
                case '%':
                    *buf++ = '%';
                    fmt++;
                    continue;
                default:
                    *buf++ = *fmt++;
            }
            if (sign) {
                if (i64 < 0) {
                    *buf++ = '-';
                    ui64 = (uint64_t) -i64;
                } else {
                    ui64 = (uint64_t) i64;
                }
            }
            buf = xxc_sprintf_num(buf, last, ui64, zero, hex, width);
            fmt++;
        }else{
            *buf++ = *fmt++;
        }
    }
    return buf;
}

static u_char* xxc_sprintf_num(u_char *buf, u_char *last, uint64_t ui64, u_char zero, xxc_uint_t hexadecimal, xxc_uint_t width){
    /**@breif: 64bit */
    u_char         *p, temp[XXC_INT64_LEN+1];
    size_t          len;
    uint32_t        ui32;
    static u_char   hex[] = "0123456789abcdef";
    static u_char   HEX[] = "0123456789ABCDEF";
    p = temp + XXC_INT64_LEN;
    if(hexadecimal == 0){
        if(ui64 <= (uint32_t)XXC_MAX_UINT32_VALUE){
            ui32 = (uint32_t) ui64;
            do {
                *--p = (u_char) (ui32 % 10 + '0');
            } while (ui32 /= 10);
        }else{
            do {
                *--p = (u_char) (ui64 % 10 + '0');
            } while (ui64 /= 10);
        }
    }else if(hexadecimal == 1){
        do {
            *--p = hex[(uint32_t) (ui64 & 0xf)];
        } while (ui64 >>= 4);
    }else {
        do {
            *--p = HEX[(uint32_t) (ui64 & 0xf)];
        } while (ui64 >>= 4);
    }
    len = (temp + XXC_INT64_LEN) - p;
    while (len++ < width && buf < last) {
        *buf++ = zero;
    }
    len = (temp + XXC_INT64_LEN) - p;
    if (buf + len > last) {
        len = last - buf;
    }
    //TO DO
    return xxc_cpymem(buf, p, len);
}