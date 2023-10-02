#include "p101_posix_xsi/sys/p101_msg.h"


int p101_msgctl(const struct p101_env *env, struct p101_error *err, int msqid, int cmd, struct msqid_ds *buf)
{
    int ret_val;

    P101_TRACE(env);
    errno = 0;
    ret_val = msgctl(msqid, cmd, buf);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_msgget(const struct p101_env *env, struct p101_error *err, key_t key, int msgflg)
{
    int ret_val;

    P101_TRACE(env);
    errno = 0;
    ret_val = msgget(key, msgflg);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

ssize_t p101_msgrcv(const struct p101_env *env, struct p101_error *err, int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg)
{
    ssize_t ret_val;

    P101_TRACE(env);
    errno = 0;
    ret_val = msgrcv(msqid, msgp, msgsz, msgtyp, msgflg);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}

int p101_msgsnd(const struct p101_env *env, struct p101_error *err, int msqid, const void *msgp, size_t msgsz, int msgflg)
{
    int ret_val;

    P101_TRACE(env);
    errno = 0;
    ret_val = msgsnd(msqid, msgp, msgsz, msgflg);

    if(ret_val == -1)
    {
        P101_ERROR_RAISE_ERRNO(err, errno);
    }

    return ret_val;
}
