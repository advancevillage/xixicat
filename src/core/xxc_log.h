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

typedef int                     xxc_fd_t;
typedef struct xxc_open_file_s   xxc_open_file_t;  
typedef struct xxc_log_s        xxc_log_t;


struct xxc_open_file_s {
    xxc_fd_t    fd;
    xxc_str_t   name;
};

struct xxc_log_s {
    xxc_uint_t          log_level;
    xxc_open_file_t     *file;
    xxc_log_t          *next;
};

#define xxc_open_file(name, mode, create, access)   open((const char *) name, mode|create, access)

xxc_log_t*  xxc_log_init(xxc_str_t *prefix);

#endif /* _XXC_LOG_H_INCLUDED_ */