#include "p101_posix_xsi/sys/p101_stat.h"
#include <sys/stat.h>


int p101_mknod(const struct p101_env *env, struct p101_error *err, const char *path, mode_t mode, dev_t dev)
{
    int ret_val;

    P101_TRACE(env);
    errno = 0;
    ret_val = mknod(path, mode, dev);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}
