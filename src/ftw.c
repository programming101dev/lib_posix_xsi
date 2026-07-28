#include "p101_posix_xsi/p101_ftw.h"
#include "p101_posix_xsi_internal.h"

struct nftw_callback_context
{
    int (*callback)(const char *, const struct stat *, int, struct FTW *);
    int                           stopped;
    struct nftw_callback_context *previous;
};

static _Thread_local struct nftw_callback_context *active_nftw_context;    // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

static int call_nftw_callback(const char *path, const struct stat *status, int type, struct FTW *walk)
{
    struct nftw_callback_context *context;
    int                           result;

    context = active_nftw_context;
    result  = context->callback(path, status, type, walk);
    if(result != 0)
    {
        context->stopped = 1;
    }

    return result;
}

/* cppcheck-suppress funcArgNamesDifferentUnnamed */
int p101_nftw(const struct p101_env *env, struct p101_error *err, const char *path, int (*fn)(const char *, const struct stat *, int, struct FTW *), int fd_limit, int flags)
{
    struct nftw_callback_context context;
    int                          saved_errno;
    int                          ret_val;

    P101_TRACE(env);
    P101_POSIX_XSI_FAULT_RETURN(env, err, -1);
    context.callback = fn;
    context.stopped  = 0;
    context.previous = active_nftw_context;

    active_nftw_context = &context;
    errno               = 0;
    ret_val             = nftw(path, call_nftw_callback, fd_limit, flags);
    saved_errno         = errno;
    active_nftw_context = context.previous;

    if(ret_val == -1 && context.stopped == 0)
    {
        P101_ERROR_RAISE_ERRNO(err, (saved_errno == 0) ? EIO : saved_errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}
