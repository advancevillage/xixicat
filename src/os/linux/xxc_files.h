/**
 * Copyright (C) richard sun
 */
#ifndef _XXC_FILES_H_INCLUDED_
#define _XXC_FILES_H_INCLUDED_

#include <xxc_config.h>
#include <xxc_core.h>

#define XXC_FILE_RDONLY          O_RDONLY
#define XXC_FILE_WRONLY          O_WRONLY
#define XXC_FILE_RDWR            O_RDWR
#define XXC_FILE_CREATE_OR_OPEN  O_CREAT
#define XXC_FILE_OPEN            0
#define XXC_FILE_TRUNCATE        (O_CREAT|O_TRUNC)
#define XXC_FILE_APPEND          (O_WRONLY|O_APPEND)
#define XXC_FILE_NONBLOCK        O_NONBLOCK

#define XXC_FILE_DEFAULT_ACCESS  0644
#define XXC_FILE_OWNER_ACCESS    0600

#define XXC_INVALID_FILE         -1
#define XXC_FILE_ERROR           -1


#define xxc_open_file(name, mode, create, access)   open((const char *) name, mode|create, access)


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

#define xxc_write_console               xxc_write_fd
#define xxc_fd_info(fd, sb)             fstat(fd, sb)
#define xxc_read_file(fd, buf, n)        read(fd,buf,n)

#define xxc_stdout               STDOUT_FILENO
#define xxc_stderr               STDERR_FILENO



#endif /* _XXC_FILES_H_INCLUDED_ */