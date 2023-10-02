#include "p101_posix_xsi/p101_wchar.h"
#include <wchar.h>

int p101_wcswidth(const struct p101_env *env, const wchar_t *pwcs, size_t n)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = wcswidth(pwcs, n);

    return ret_val;
}

int p101_wcwidth(const struct p101_env *env, wchar_t wc)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = wcwidth(wc);

    return ret_val;
}
