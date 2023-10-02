#include "p101_posix_xsi/p101_grp.h"
#include <grp.h>

void p101_endgrent(const struct p101_env *env, struct p101_error *err)
{
    P101_TRACE(env);
    errno = 0;
    endgrent();

    if(errno != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }
}

struct group *p101_getgrent(const struct p101_env *env, struct p101_error *err)
{
    struct group *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getgrent();

    if(ret_val == NULL && errno != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

void p101_setgrent(const struct p101_env *env, struct p101_error *err)
{
    P101_TRACE(env);
    errno = 0;
    setgrent();

    if(errno != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }
}
