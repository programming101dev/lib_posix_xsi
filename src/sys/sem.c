#include "p101_posix_xsi/sys/p101_sem.h"


int p101_semctl(const struct p101_env *env, struct p101_error *err, int semid, int semnum, int cmd, ...)
{
    int ret_val;

    P101_TRACE(env);
    errno = 0;
    // TODO: can I even handle this?
    ret_val = semctl(semid, semnum, cmd, 0);

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
    errno = 0;
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
    errno = 0;
    ret_val = semop(semid, sops, nsops);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}
