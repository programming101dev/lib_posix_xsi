#include "p101_posix_xsi/sys/p101_ipc.h"
#include <sys/ipc.h>


key_t p101_ftok(const struct p101_env *env, struct p101_error *err, const char *path, int id)
{
    key_t ret_val;

    P101_TRACE(env);
    errno = 0;
    ret_val = ftok(path, id);

    if(ret_val == (key_t)-1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}
