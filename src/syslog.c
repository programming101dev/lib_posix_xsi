#include "p101_posix_xsi/p101_syslog.h"
#include <syslog.h>

void p101_closelog(const struct p101_env *env)
{
    P101_TRACE(env);
    errno = 0;
    closelog();
}

void p101_openlog(const struct p101_env *env, const char *ident, int logopt, int facility)
{
    P101_TRACE(env);
    errno = 0;
    openlog(ident, logopt, facility);
}

int p101_setlogmask(const struct p101_env *env, int maskpri)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = setlogmask(maskpri);

    return ret_val;
}
