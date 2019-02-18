/**
 * Copyright (C) richard sun
 */
#include <xxc_config.h>
#include <xxc_core.h>

static xxc_str_t log_levels[] = {
    xxc_null_string,
    xxc_string("emerg"),
    xxc_string("alert"),
    xxc_string("crit"),
    xxc_string("error"),
    xxc_string("warn"),
    xxc_string("notice"),
    xxc_string("info"),
    xxc_string("debug")
};

static xxc_log_t        xxc_log;
static xxc_open_file_t   xxc_log_file;

xxc_log_t*  xxc_log_init(xxc_str_t *name) {
    xxc_log_file.name.data = name->data;
    xxc_log_file.name.len = name->len;
    xxc_log.file = &xxc_log_file;
    xxc_log.log_level = XXC_LOG_NOTICE;
    xxc_log_file.fd = xxc_open_file(name->data,XXC_FILE_APPEND,XXC_FILE_CREATE_OR_OPEN,XXC_FILE_DEFAULT_ACCESS);
    return &xxc_log;
}