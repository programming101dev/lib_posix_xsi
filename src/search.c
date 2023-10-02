#include "p101_posix_xsi/p101_search.h"

int p101_hcreate(const struct p101_env *env, struct p101_error *err, size_t nel)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = hcreate(nel);

    if(ret_val == 0)
    {
        P101_ERROR_RAISE_ERRNO(err, ret_val);
    }

    return ret_val;
}

void p101_hdestroy(const struct p101_env *env)
{
    P101_TRACE(env);
    errno = 0;
    hdestroy();
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

ENTRY *p101_hsearch(const struct p101_env *env, struct p101_error *err, ENTRY item, ACTION action)
{
    ENTRY *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = hsearch(item, action);

    if(ret_val == 0)
    {
        // TODO: what?
    }

    return ret_val;
}

#pragma GCC diagnostic pop

void p101_insque(const struct p101_env *env, void *element, void *pred)
{
    P101_TRACE(env);
    errno = 0;
    insque(element, pred);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void *p101_lfind(const struct p101_env *env, struct p101_error *err, const void *key, const void *base, size_t *nelp, size_t width, int (*compar)(const void *, const void *))
{
    void *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = lfind(key, base, nelp, width, compar);

    if(ret_val == NULL)
    {
        // TODO: what?
    }

    return ret_val;
}

#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void *p101_lsearch(const struct p101_env *env, struct p101_error *err, const void *key, void *base, size_t *nelp, size_t width, int (*compar)(const void *, const void *))
{
    void *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = lsearch(key, base, nelp, width, compar);

    if(ret_val == NULL)
    {
        // TODO: what?
    }

    return ret_val;
}

#pragma GCC diagnostic pop

void p101_remque(const struct p101_env *env, void *element)
{
    P101_TRACE(env);
    errno = 0;
    remque(element);
}

void *p101_tdelete(const struct p101_env *env, const void *restrict key, void **restrict rootp, int (*compar)(const void *, const void *))
{
    void *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = tdelete(key, rootp, compar);

    return ret_val;
}

void *p101_tfind(const struct p101_env *env, const void *key, void *const *rootp, int (*compar)(const void *, const void *))
{
    void *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = tfind(key, rootp, compar);

    return ret_val;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void *p101_tsearch(const struct p101_env *env, struct p101_error *err, const void *key, void **rootp, int (*compar)(const void *, const void *))
{
    void *ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = tsearch(key, rootp, compar);

    if(ret_val == NULL)
    {
        // TODO: what?
    }

    return ret_val;
}

#pragma GCC diagnostic pop

void p101_twalk(const struct p101_env *env, const void *root, void (*action)(const void *, VISIT, int))
{
    P101_TRACE(env);
    errno = 0;
    twalk(root, action);
}
