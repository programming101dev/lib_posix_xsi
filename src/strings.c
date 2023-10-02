#include "p101_posix_xsi/p101_strings.h"
#include <strings.h>

int p101_ffs(const struct p101_env *env, int i)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = ffs(i);

    return ret_val;
}
