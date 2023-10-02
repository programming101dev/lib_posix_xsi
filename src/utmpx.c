#include "p101_posix_xsi/p101_utmpx.h"
#include <utmpx.h>

void p101_endutxent(const struct p101_env *env)
{
    P101_TRACE(env);
    errno = 0;
    endutxent();
}

struct utmpx *p101_getutxent(const struct p101_env *env)
{
    struct utmpx *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getutxent();

    return ret_val;
}

struct utmpx *p101_getutxid(const struct p101_env *env, const struct utmpx *id)
{
    struct utmpx *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getutxid(id);

    return ret_val;
}

struct utmpx *p101_getutxline(const struct p101_env *env, const struct utmpx *line)
{
    struct utmpx *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = getutxline(line);

    return ret_val;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

struct utmpx *p101_pututxline(const struct p101_env *env, struct p101_error *err, const struct utmpx *utmpx)
{
    struct utmpx *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = pututxline(utmpx);

    if(ret_val == NULL)
    {
        // TODO: what?
    }

    return ret_val;
}

#pragma GCC diagnostic pop

void p101_setutxent(const struct p101_env *env)
{
    P101_TRACE(env);
    errno = 0;
    setutxent();
}
