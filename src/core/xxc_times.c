/**
 * Copyright (C) richard sun
 */
#include <xxc_config.h>
#include <xxc_core.h>

#define XXC_TIME_SLOTS   64

static xxc_uint_t    slot;
static u_char        log_iso8601[XXC_TIME_SLOTS][sizeof("1970-09-28T12:00:00+0600")];

static      xxc_time_t        cached_time[XXC_TIME_SLOTS];
volatile    xxc_time_t       *xxc_cached_time;
volatile    xxc_str_t         xxc_log_iso8601;

void xxc_time_init(void) {
    xxc_log_iso8601.len = sizeof("1970-09-28T12:00:00+0600") - 1;
    xxc_cached_time = &cached_time[0];
    xxc_time_update();
}

void xxc_time_update(void) {
    printf("%s\n", "TODO");
}