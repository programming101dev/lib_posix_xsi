/*
 * Bounded parser and string-contract fuzz harness for lib_posix_xsi.
 */
#include <p101_env/env.h>
#include <p101_error/error.h>
#include <p101_posix_xsi/p101_libgen.h>
#include <p101_posix_xsi/p101_math.h>
#include <p101_posix_xsi/p101_string.h>
#include <p101_posix_xsi/p101_time.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum
{
    MAX_FUZZ_TEXT = 4096
};

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    struct p101_error *err;
    struct p101_env   *env;
    struct tm          parsed = {0};
    char               first[MAX_FUZZ_TEXT + 1];
    char               second[MAX_FUZZ_TEXT + 1];
    char               destination[MAX_FUZZ_TEXT + 1];
    double             number = 0.0;

    if(size > MAX_FUZZ_TEXT)
    {
        return 0;
    }

    memcpy(first, data, size);
    memcpy(second, data, size);
    first[size]  = '\0';
    second[size] = '\0';

    err = p101_error_create(false);
    if(err == NULL)
    {
        return 0;
    }
    env = p101_env_create(err, NULL);
    if(env == NULL)
    {
        p101_error_destroy(err);
        return 0;
    }

    (void)p101_strptime(env, first, "%Y-%m-%d %H:%M:%S", &parsed);
    (void)p101_basename(env, first);
    (void)p101_dirname(env, second);
    (void)p101_memccpy(env, destination, data, '\0', size);

    if(size >= sizeof(number))
    {
        memcpy(&number, data, sizeof(number));
        (void)p101_j0(env, err, number);
        p101_error_reset(err);
        (void)p101_y0(env, err, number);
    }

    p101_env_destroy(env);
    p101_error_destroy(err);
    return 0;
}
