#include "../p101_posix_xsi_internal.h"
#include "p101_posix_xsi/sys/p101_ipc.h"
#include <sys/ipc.h>

key_t p101_ftok(const struct p101_env *env, struct p101_error *err, const char *path, int id)
{
    key_t ret_val;

    P101_TRACE(env);
    P101_POSIX_XSI_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = ftok(path, id);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}
