#include "p101_posix_xsi/p101_stdlib.h"
#include "p101_posix_xsi_internal.h"
#include <p101_c/p101_string.h>
#include <stdlib.h>
#include <string.h>

long p101_a64l(const struct p101_env *env, const char *s)
{
    long ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = a64l(s);

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_grantpt(const struct p101_env *env, struct p101_error *err, int fildes)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_XSI_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = grantpt(fildes);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

char *p101_initstate(const struct p101_env *env, struct p101_error *err, unsigned seed, char *state, size_t size)
{
    char *ret_val;

    P101_TRACE(env);
    P101_POSIX_XSI_FAULT_RETURN(env, err, NULL);
    errno   = 0;
    ret_val = initstate(seed, state, size);

    if(ret_val == NULL)
    {
        if(errno != 0)
        {
            P101_ERROR_RAISE_ERRNO(err, errno);
        }
        else
        {
            P101_ERROR_RAISE_ERRNO(err, EINVAL);
        }
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

char *p101_l64a(const struct p101_env *env, long value)
{
    char *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = l64a(value);

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_posix_openpt(const struct p101_env *env, struct p101_error *err, int oflag)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_XSI_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = posix_openpt(oflag);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }
    else
    {
        P101_TRACK_OPEN(env, ret_val);
    }

    P101_TRACE_EXIT(env);

    return ret_val;
}

char *p101_ptsname(const struct p101_env *env, struct p101_error *err, int fildes)
{
    char *ret_val;

    P101_TRACE(env);
    P101_POSIX_XSI_FAULT_RETURN(env, err, NULL);
    errno   = 0;
    ret_val = ptsname(fildes);

    if(ret_val == NULL)
    {
        P101_ERROR_RAISE_ERRNO(err, (errno == 0) ? EIO : errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_putenv(const struct p101_env *env, struct p101_error *err, char *string)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_XSI_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = putenv(string);

    if(ret_val != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

char *p101_realpath(const struct p101_env *env, struct p101_error *err, const char *restrict file_name, char *restrict resolved_name)
{
    char *ret_val;

    P101_TRACE(env);
    P101_POSIX_XSI_FAULT_RETURN(env, err, NULL);
    errno   = 0;
    ret_val = realpath(file_name, resolved_name);

    if(ret_val == NULL)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }
    else if(resolved_name == NULL)
    {
        P101_TRACK_ALLOC(env, ret_val, p101_strlen(env, ret_val) + 1U);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

unsigned short *p101_seed48(const struct p101_env *env, unsigned short seed16v[3])    // cppcheck-suppress constParameter
{
    unsigned short *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = seed48(seed16v);

    P101_TRACE_EXIT(env);
    return ret_val;
}

char *p101_setstate(const struct p101_env *env, struct p101_error *err, char *state)
{
    char *ret_val;

    P101_TRACE(env);
    P101_POSIX_XSI_FAULT_RETURN(env, err, NULL);
    errno   = 0;
    ret_val = setstate(state);

    if(ret_val == NULL)
    {
        if(errno != 0)
        {
            P101_ERROR_RAISE_ERRNO(err, errno);
        }
        else
        {
            P101_ERROR_RAISE_ERRNO(err, EINVAL);
        }
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

void p101_srand48(const struct p101_env *env, long seedval)
{
    P101_TRACE(env);
    errno = 0;
    srand48(seedval);
    P101_TRACE_EXIT(env);
}

void p101_srandom(const struct p101_env *env, unsigned seed)
{
    P101_TRACE(env);
    errno = 0;
    srandom(seed);
    P101_TRACE_EXIT(env);
}

int p101_unlockpt(const struct p101_env *env, struct p101_error *err, int fildes)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_XSI_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = unlockpt(fildes);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}
