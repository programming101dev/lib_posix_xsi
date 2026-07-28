#include "../p101_posix_xsi_internal.h"
#include "p101_posix_xsi/sys/p101_sem.h"

static int semctl_uses_arg(int cmd);

static int semctl_uses_arg(int cmd)
{
    return cmd == GETALL || cmd == SETALL || cmd == SETVAL || cmd == IPC_STAT || cmd == IPC_SET;
}

int p101_semctl(const struct p101_env *env, struct p101_error *err, int semid, int semnum, int cmd)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_XSI_FAULT_RETURN(env, err, -1);

    if(semctl_uses_arg(cmd))
    {
        P101_ERROR_RAISE_ERRNO(err, EINVAL);
        P101_TRACE_EXIT(env);
        return -1;
    }

    errno   = 0;
    ret_val = semctl(semid, semnum, cmd);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_semctl_arg(const struct p101_env *env, struct p101_error *err, int semid, int semnum, int cmd, union p101_semun arg)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_XSI_FAULT_RETURN(env, err, -1);

    if(!semctl_uses_arg(cmd))
    {
        P101_ERROR_RAISE_ERRNO(err, EINVAL);
        P101_TRACE_EXIT(env);
        return -1;
    }

    errno = 0;
#ifdef __clang__
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wclass-varargs"
#endif
    ret_val = semctl(semid, semnum, cmd, arg);
#ifdef __clang__
    #pragma clang diagnostic pop
#endif

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_semget(const struct p101_env *env, struct p101_error *err, key_t key, int nsems, int semflg)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_XSI_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = semget(key, nsems, semflg);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

int p101_semop(const struct p101_env *env, struct p101_error *err, int semid, struct sembuf *sops, size_t nsops)
{
    int ret_val;

    P101_TRACE(env);
    P101_POSIX_XSI_FAULT_RETURN(env, err, -1);
    errno   = 0;
    ret_val = semop(semid, sops, nsops);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}
