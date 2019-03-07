/**
 * Copyright (C) richard sun
 */
#include <xxc_config.h>
#include <xxc_core.h>
#include <xixicat.h>

/* Create a bunch of objects as demonstration. */
static int print_preallocated(cJSON *root)
{
    /* declarations */
    char *out = NULL;
    char *buf = NULL;
    char *buf_fail = NULL;
    size_t len = 0;
    size_t len_fail = 0;

    /* formatted print */
    out = cJSON_Print(root);

    /* create buffer to succeed */
    /* the extra 5 bytes are because of inaccuracies when reserving memory */
    len = strlen(out) + 5;
    buf = (char*)malloc(len);
    if (buf == NULL)
    {
        printf("Failed to allocate memory.\n");
        exit(1);
    }

    /* create buffer to fail */
    len_fail = strlen(out);
    buf_fail = (char*)malloc(len_fail);
    if (buf_fail == NULL)
    {
        printf("Failed to allocate memory.\n");
        exit(1);
    }

    /* Print to buffer */
    if (!cJSON_PrintPreallocated(root, buf, (int)len, 1)) {
        printf("cJSON_PrintPreallocated failed!\n");
        if (strcmp(out, buf) != 0) {
            printf("cJSON_PrintPreallocated not the same as cJSON_Print!\n");
            printf("cJSON_Print result:\n%s\n", out);
            printf("cJSON_PrintPreallocated result:\n%s\n", buf);
        }
        free(out);
        free(buf_fail);
        free(buf);
        return -1;
    }

    /* success */
    printf("%s\n", buf);

    /* force it to fail */
    if (cJSON_PrintPreallocated(root, buf_fail, (int)len_fail, 1)) {
        printf("cJSON_PrintPreallocated failed to show error with insufficient memory!\n");
        printf("cJSON_Print result:\n%s\n", out);
        printf("cJSON_PrintPreallocated result:\n%s\n", buf_fail);
        free(out);
        free(buf_fail);
        free(buf);
        return -1;
    }

    free(out);
    free(buf_fail);
    free(buf);
    return 0;
}


int xxc_cdecl main(int argc, char* argv[]) {
    xxc_int_t  t = 112;
    printf("n = %ld\n", t);
    printf("xixicat's version is %s\n", xixicat_version);

    printf("t up is %c\n", xxc_toupper('t'));
    printf("T lower is %c\n", xxc_toupper('T'));
    xxc_str_t src = xxc_string("hello xixicat!");   
    u_char *dst = (u_char*)malloc(sizeof(u_char) * 20);
    memset(dst, 0, 20);
    printf("src data is %s\n len is %ld\n", src.data,src.len);
    xxc_strup(dst, src.data, src.len);
    printf("dst is %s\n", dst);

    //buf
    xxc_str_t richard = xxc_string("richard");
    xxc_str_t kelly = xxc_string("kelly");
    u_char buf[100];
    xxc_sprintf(buf, "%V", &src);
    printf("%s\n", buf);
    xxc_sprintf(buf,"xxc_int_t is %i", t);
    printf("%s\n", buf);
    memset(buf, 0, sizeof(buf));
    double f = 100.0001;
    xxc_sprintf(buf,"f is %.4f", f);
    printf("%s\n", buf);
    xxc_sprintf(buf, "%*s",5,dst);
    printf("%s\n", buf);
    time_t sec = xxc_time(&richard);
    xxc_str_t   file = xxc_string("./src/test/xixicat.log");
    xxc_log_t   *log;
    log = xxc_log_init(&file);
    xxc_json_t  *root;
    const char *strings[7] =
    {
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday"
    };
    root = xxc_json_create_string_array(strings, 7);
    // print_preallocated(root);

    u_char *cf = (u_char*)"./src/test/xixicat.json";
    xxc_json_t *config = xxc_json_parse_file(cf, log);
    print_preallocated(config);
    return XXC_OK;
}