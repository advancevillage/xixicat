/**
 * Copyright (C) richard sun
 */
#ifndef _XXC_LOG_H_INCLUDED_
#define  _XXC_LOG_H_INCLUDED_

#include <xxc_config.h>
#include <xxc_core.h>

#define XXC_LOG_STDERR            0
#define XXC_LOG_EMERG             1
#define XXC_LOG_ALERT             2
#define XXC_LOG_CRIT              3
#define XXC_LOG_ERR               4
#define XXC_LOG_WARN              5
#define XXC_LOG_NOTICE            6
#define XXC_LOG_INFO              7
#define XXC_LOG_DEBUG             8

#define XXC_MAX_ERROR_STR         2048

typedef struct xxc_log_s        xxc_log_t;

struct xxc_log_s {
    xxc_uint_t          log_level;
    xxc_open_file_t     *file;
    xxc_log_t          *next;
};

/**
 *@brief: 初始化日志文件并尝试
 *@param: name 日志文件路径
 *@retval: 返回xxx_log_t指针
 */
xxc_log_t*  xxc_log_init(xxc_str_t *name);

/**
 *@brief: 标准错误输出
 *@param:
 */
void xxc_cdecl xxc_log_stderr(xxc_err_t err, const char *fmt, ...);

/**
 *@breif: 封装系统write系统调用
 *@param: fd 文件描述符
 *@param: buf 数据指针
 *@param: n 前n个字符
 *@retval: 
 */
static xxc_inline ssize_t xxc_write_fd(xxc_fd_t fd, void *buf, size_t n) {
    return write(fd, buf, n);
}

#define xxc_write_console        xxc_write_fd

#define xxc_stdout               STDOUT_FILENO
#define xxc_stderr               STDERR_FILENO

#endif /* _XXC_LOG_H_INCLUDED_ */