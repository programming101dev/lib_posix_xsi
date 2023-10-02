#include "p101_posix_xsi/p101_dirent.h"

void p101_seekdir(const struct p101_env *env, DIR *dirp, long loc)
{
    P101_TRACE(env);
    errno = 0;
    seekdir(dirp, loc);
}

long p101_telldir(const struct p101_env *env, DIR *dirp)
{
    long ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = telldir(dirp);

    return ret_val;
}
