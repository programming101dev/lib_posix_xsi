#include "p101_posix_xsi/p101_pwd.h"
#include <pwd.h>

void p101_endpwent(const struct p101_env *env, struct p101_error *err)
{
    P101_TRACE(env);
    errno = 0;
    endpwent();

    if(errno != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }
}

struct passwd *p101_getpwent(const struct p101_env *env, struct p101_error *err)
{
    struct passwd *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getpwent();

    if(ret_val == NULL && errno != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

void p101_setpwent(const struct p101_env *env, struct p101_error *err)
{
    P101_TRACE(env);
    errno = 0;
    setpwent();

    if(errno != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }
}
