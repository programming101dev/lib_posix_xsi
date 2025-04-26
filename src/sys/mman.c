#include "p101_posix_xsi/sys/p101_mman.h"
#include <sys/mman.h>

int p101_msync(const struct p101_env *env, struct p101_error *err, void *addr, size_t len, int flags)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = msync(addr, len, flags);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}
