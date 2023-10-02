#include "p101_posix_xsi/p101_math.h"
#include <math.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

double p101_j0(const struct p101_env *env, struct p101_error *err, double x)
{
    double ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = j0(x);

    return ret_val;
}

#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

double p101_j1(const struct p101_env *env, struct p101_error *err, double x)
{
    double ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = j1(x);

    return ret_val;
}

#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

double p101_jn(const struct p101_env *env, struct p101_error *err, int n, double x)
{
    double ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = jn(n, x);

    return ret_val;
}

#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

double p101_y0(const struct p101_env *env, struct p101_error *err, double x)
{
    double ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = y0(x);

    return ret_val;
}

#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

double p101_y1(const struct p101_env *env, struct p101_error *err, double x)
{
    double ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = y1(x);

    return ret_val;
}

#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

double p101_yn(const struct p101_env *env, struct p101_error *err, int n, double x)
{
    double ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = yn(n, x);

    return ret_val;
}

#pragma GCC diagnostic pop
