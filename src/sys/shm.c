#include "p101_posix_xsi/sys/p101_shm.h"

void *p101_shmat(const struct p101_env *env, struct p101_error *err, int shmid, const void *shmaddr, int shmflg)
{
    void *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = shmat(shmid, shmaddr, shmflg);

    if(ret_val == (void *)-1)    // NOLINT(performance-no-int-to-ptr)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_shmctl(const struct p101_env *env, struct p101_error *err, int shmid, int cmd, struct shmid_ds *buf)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = shmctl(shmid, cmd, buf);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_shmdt(const struct p101_env *env, struct p101_error *err, const void *shmaddr)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = shmdt(shmaddr);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_shmget(const struct p101_env *env, struct p101_error *err, key_t key, size_t size, int shmflg)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = shmget(key, size, shmflg);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}
