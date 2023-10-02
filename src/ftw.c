#include "p101_posix_xsi/p101_ftw.h"

int p101_nftw(const struct p101_env *env, struct p101_error *err, const char *path, int (*fn)(const char *, const struct stat *, int, struct FTW *), int fd_limit, int flags)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = nftw(path, fn, fd_limit, flags);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}
