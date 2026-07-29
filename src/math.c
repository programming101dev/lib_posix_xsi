#include "p101_posix_xsi/p101_math.h"
#include "p101_posix_xsi_internal.h"
#include <fenv.h>
#include <math.h>
#include <p101_c/p101_fenv.h>
#include <p101_c/p101_math.h>

static int bessel_error_code(const struct p101_env *env);
static int bessel_y_error_code(const struct p101_env *env, double x);
static int prepare_bessel_call(const struct p101_env *env, struct p101_error *err);

static int bessel_error_code(const struct p101_env *env)
{
    int exceptions;

    if(errno != 0)
    {
        return errno;
    }

    exceptions = p101_fetestexcept(env, FE_INVALID | FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW);

    if((exceptions & FE_INVALID) != 0)
    {
        return EDOM;
    }

    if((exceptions & (FE_DIVBYZERO | FE_OVERFLOW | FE_UNDERFLOW)) != 0)
    {
        return ERANGE;
    }

    return 0;
}

static int bessel_y_error_code(const struct p101_env *env, double x)
{
    int error_code;

    error_code = bessel_error_code(env);
    if(error_code != 0)
    {
        return error_code;
    }

    /*
     * Some supported libm implementations return the required exceptional
     * value without setting errno or a floating-point exception. The XSI
     * domain itself is still unambiguous.
     */
    if(x < 0.0)
    {
        return EDOM;
    }

    if(fpclassify(x) == FP_ZERO)
    {
        return ERANGE;
    }

    return 0;
}

static int prepare_bessel_call(const struct p101_env *env, struct p101_error *err)
{
    errno = 0;
    return p101_feclearexcept(env, err, FE_ALL_EXCEPT);
}

double p101_j0(const struct p101_env *env, struct p101_error *err, double x)
{
    int    error_code;
    double ret_val;

    P101_TRACE(env);
    P101_POSIX_XSI_FAULT_RETURN(env, err, p101_nan(env, ""));
    if(prepare_bessel_call(env, err) != 0)
    {
        P101_TRACE_EXIT(env);
        return p101_nan(env, "");
    }
    ret_val    = j0(x);
    error_code = bessel_error_code(env);

    if(error_code != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, error_code);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

double p101_j1(const struct p101_env *env, struct p101_error *err, double x)
{
    int    error_code;
    double ret_val;

    P101_TRACE(env);
    P101_POSIX_XSI_FAULT_RETURN(env, err, p101_nan(env, ""));
    if(prepare_bessel_call(env, err) != 0)
    {
        P101_TRACE_EXIT(env);
        return p101_nan(env, "");
    }
    ret_val    = j1(x);
    error_code = bessel_error_code(env);

    if(error_code != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, error_code);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

double p101_jn(const struct p101_env *env, struct p101_error *err, int n, double x)
{
    int    error_code;
    double ret_val;

    P101_TRACE(env);
    P101_POSIX_XSI_FAULT_RETURN(env, err, p101_nan(env, ""));
    if(prepare_bessel_call(env, err) != 0)
    {
        P101_TRACE_EXIT(env);
        return p101_nan(env, "");
    }
    ret_val    = jn(n, x);
    error_code = bessel_error_code(env);

    if(error_code != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, error_code);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

double p101_y0(const struct p101_env *env, struct p101_error *err, double x)
{
    int    error_code;
    double ret_val;

    P101_TRACE(env);
    P101_POSIX_XSI_FAULT_RETURN(env, err, p101_nan(env, ""));
    if(prepare_bessel_call(env, err) != 0)
    {
        P101_TRACE_EXIT(env);
        return p101_nan(env, "");
    }
    ret_val    = y0(x);
    error_code = bessel_y_error_code(env, x);

    if(error_code != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, error_code);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

double p101_y1(const struct p101_env *env, struct p101_error *err, double x)
{
    int    error_code;
    double ret_val;

    P101_TRACE(env);
    P101_POSIX_XSI_FAULT_RETURN(env, err, p101_nan(env, ""));
    if(prepare_bessel_call(env, err) != 0)
    {
        P101_TRACE_EXIT(env);
        return p101_nan(env, "");
    }
    ret_val    = y1(x);
    error_code = bessel_y_error_code(env, x);

    if(error_code != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, error_code);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}

double p101_yn(const struct p101_env *env, struct p101_error *err, int n, double x)
{
    int    error_code;
    double ret_val;

    P101_TRACE(env);
    P101_POSIX_XSI_FAULT_RETURN(env, err, p101_nan(env, ""));
    if(prepare_bessel_call(env, err) != 0)
    {
        P101_TRACE_EXIT(env);
        return p101_nan(env, "");
    }
    ret_val    = yn(n, x);
    error_code = bessel_y_error_code(env, x);

    if(error_code != 0)
    {
        P101_ERROR_RAISE_ERRNO(err, error_code);
    }

    P101_TRACE_EXIT(env);
    return ret_val;
}
