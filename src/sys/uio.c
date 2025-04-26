#include "p101_posix_xsi/sys/p101_uio.h"

ssize_t p101_readv(const struct p101_env *env, struct p101_error *err, int fildes, const struct iovec *iov, int iovcnt)
{
    ssize_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = readv(fildes, iov, iovcnt);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

ssize_t p101_writev(const struct p101_env *env, struct p101_error *err, int fildes, const struct iovec *iov, int iovcnt)
{
    ssize_t ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = writev(fildes, iov, iovcnt);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}
