/**
 * Copyright (C) richard sun
 */
#include <xxc_config.h>
#include <xxc_core.h>
#include <xixicat.h>

int xxc_cdecl main(int argc, char* argv[]) {
    xxc_int_t  t = 12;
    printf("n = %ld\n", t);
    printf("xixicat's version is %s\n", xixicat_version);
    return XXC_OK;
}