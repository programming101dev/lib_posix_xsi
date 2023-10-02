#include "p101_posix_xsi/p101_time.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

char *p101_strptime(const struct p101_env *env, struct p101_error *err, const char *restrict buf, const char *restrict format, struct tm *restrict tm)
{
    char *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = strptime(buf, format, tm);

    if(ret_val == NULL)
    {
        // TODO: is this an error?
    }

    return ret_val;
}

#pragma GCC diagnostic pop
