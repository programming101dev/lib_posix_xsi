#include "p101_posix_xsi/sys/p101_time.h"
#include <sys/time.h>


int p101_utimes(const struct p101_env *env, struct p101_error *err, const char *path, const struct timeval times[2])
{
    int ret_val;

    P101_TRACE(env);
    errno = 0;
    ret_val = utimes(path, times);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

