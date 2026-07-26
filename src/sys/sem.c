#include "p101_posix_xsi/sys/p101_sem.h"
#include <stdarg.h>

static int semctl_uses_arg(int cmd);

static int semctl_uses_arg(int cmd)
{
    int uses_arg;

    uses_arg = (cmd == GETALL || cmd == SETALL || cmd == SETVAL || cmd == IPC_STAT || cmd == IPC_SET);

    return uses_arg;
}

int p101_semctl(const struct p101_env *env, struct p101_error *err, int semid, int semnum, int cmd, ...)
{
    int ret_val;

    P101_TRACE(env);
    errno = 0;

    if(semctl_uses_arg(cmd))
    {
        va_list     args;
        union semun arg;

        va_start(args, cmd);
        arg = va_arg(args, union semun);
        va_end(args);

#ifdef __clang__
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wclass-varargs"
#endif
        ret_val = semctl(semid, semnum, cmd, arg);
#ifdef __clang__
    #pragma clang diagnostic pop
#endif
    }
    else
    {
        ret_val = semctl(semid, semnum, cmd);
    }

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_semget(const struct p101_env *env, struct p101_error *err, key_t key, int nsems, int semflg)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = semget(key, nsems, semflg);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_semop(const struct p101_env *env, struct p101_error *err, int semid, struct sembuf *sops, size_t nsops)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = semop(semid, sops, nsops);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}
