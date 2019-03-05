/**
 * Copyright (C) richard sun
 */
#include <xxc_config.h>
#include <xxc_core.h>

static xxc_json_t      *config;
static xxc_open_file_t   config_file;

xxc_json_t* xxc_json_parse_file(u_char* file, xxc_log_t *log){
    xxc_file_info_t     info;
    u_char             buf[1024];
    memset(buf, 0, 1024);

    config_file.name.data = file;
    config_file.name.len = xxc_strlen(file);

    config_file.fd = xxc_open_file(config_file.name.data,XXC_FILE_RDONLY,XXC_FILE_OPEN,0);
    if (config_file.fd == XXC_INVALID_FILE) {
        xxc_log_stderr(xxc_errno,"[alert] could not open log file: %V failed", config_file.name);
        config_file.fd = xxc_stderr;
    }
    if (xxc_fd_info(config_file.fd, &info) == XXC_FILE_ERROR) {

    };

    if (xxc_read_file(config_file.fd, buf, info.st_size) == XXC_FILE_ERROR) {

    }

    config = xxc_json_parse((const char*)buf);

    return  config;
}