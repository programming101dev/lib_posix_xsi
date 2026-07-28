#include "p101_posix_xsi/p101_signal.h"
#include "p101_posix_xsi_internal.h"

int p101_killpg(const struct p101_env *env, struct p101_error *err, pid_t pgrp, int sig)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_XSI_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = killpg(pgrp, sig);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_sigaltstack(const struct p101_env *env, struct p101_error *err, const stack_t *restrict ss, stack_t *restrict oss)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_XSI_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = sigaltstack(ss, oss);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}
