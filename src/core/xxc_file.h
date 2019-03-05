/**
 * Copyright (C) richard sun
 */
#ifndef _XXC_FILE_H_INCLUDED_
#define _XXC_FILE_H_INCLUDED_

#include <xxc_config.h>
#include <xxc_core.h>

typedef int                     xxc_fd_t;
typedef struct stat             xxc_file_info_t;
typedef struct xxc_open_file_s   xxc_open_file_t;  


struct xxc_open_file_s {
    xxc_fd_t    fd;
    xxc_str_t   name;
};



#endif /* _XXC_FILE_H_INCLUDED_ */