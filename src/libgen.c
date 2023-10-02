#include "p101_posix_xsi/p101_libgen.h"
#include <libgen.h>

char *p101_basename(const struct p101_env *env, char *path)
{
    char *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = basename(path);

    return ret_val;
}

char *p101_dirname(const struct p101_env *env, char *path)
{
    char *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = dirname(path);

    return ret_val;
}
