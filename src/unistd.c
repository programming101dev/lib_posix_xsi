#include "p101_posix_xsi/p101_unistd.h"
#include <crypt.h>
#include <unistd.h>

char *p101_crypt(const struct p101_env *env, struct p101_error *err, const char *key, const char *salt)
{
    char *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = crypt(key, salt);    // cppcheck-suppress cryptCalled

    if(ret_val == NULL)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

long p101_gethostid(const struct p101_env *env)
{
    long ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = gethostid();

    return ret_val;
}

int p101_lockf(const struct p101_env *env, struct p101_error *err, int fildes, int function, off_t size)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = lockf(fildes, function, size);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_nice(const struct p101_env *env, struct p101_error *err, int value)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = nice(value);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_setregid(const struct p101_env *env, struct p101_error *err, gid_t rgid, gid_t egid)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = setregid(rgid, egid);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_setreuid(const struct p101_env *env, struct p101_error *err, uid_t ruid, uid_t euid)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = setreuid(ruid, euid);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

void p101_swab(const struct p101_env *env, const void *restrict src, void *restrict dest, ssize_t nbytes)
{
    P101_TRACE(env);
    errno = 0;
    swab(src, dest, nbytes);
}

void p101_sync(const struct p101_env *env)
{
    P101_TRACE(env);
    errno = 0;
    sync();
}
