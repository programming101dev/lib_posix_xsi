#include "../p101_posix_xsi_internal.h"
#include "p101_posix_xsi/sys/p101_mman.h"
#include <sys/mman.h>

int p101_msync(const struct p101_env *env, struct p101_error *err, void *addr, size_t len, int flags)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_XSI_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = msync(addr, len, flags);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}
