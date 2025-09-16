#include "p101_posix_xsi/p101_ndbm.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

int p101_dbm_clearerr(const struct p101_env *env, struct p101_error *err, DBM *db)
{
    int ret_val;

    P101_TRACE(env);
    errno = 0;
    dbm_clearerr(db);

    if(p101_dbm_error(env, db))
    {
        // TODO: what? - the spec says it is unspecified!
        ret_val = -1;
    }
    else
    {
        ret_val = 0;
    }

    return ret_val;
}

#pragma GCC diagnostic pop

void p101_dbm_close(const struct p101_env *env, DBM *db)
{
    P101_TRACE(env);
    errno = 0;
    dbm_close(db);
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

int p101_dbm_delete(const struct p101_env *env, struct p101_error *err, DBM *db, datum key)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = dbm_delete(db, key);

    if(ret_val < 0)
    {
        // TODO: what?
    }

    return ret_val;
}

#pragma GCC diagnostic pop

int p101_dbm_error(const struct p101_env *env, DBM *db)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = dbm_error(db);

    return ret_val;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Waggregate-return"

datum p101_dbm_fetch(const struct p101_env *env, struct p101_error *err, DBM *db, datum key)
{
    datum ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = dbm_fetch(db, key);

    if(ret_val.dptr == NULL)
    {
        // TODO: what?
    }

    return ret_val;
}

#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Waggregate-return"

datum p101_dbm_firstkey(const struct p101_env *env, struct p101_error *err, DBM *db)
{
    datum ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = dbm_firstkey(db);

    if(ret_val.dptr == NULL)
    {
        // TODO: what?
    }

    return ret_val;
}

#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Waggregate-return"

datum p101_dbm_nextkey(const struct p101_env *env, struct p101_error *err, DBM *db)
{
    datum ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = dbm_nextkey(db);

    if(ret_val.dptr == NULL)
    {
        // TODO: what?
    }

    return ret_val;
}

#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

DBM *p101_dbm_open(const struct p101_env *env, struct p101_error *err, const char *file, int open_flags, mode_t file_mode)
{
    DBM *ret_val;

    P101_TRACE(env);
    errno = 0;
#pragma GCC diagnostic push
#if defined(__GNUC__) && !defined(__clang__)
    #pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
#endif
#ifdef __clang__
    #pragma GCC diagnostic ignored "-Wincompatible-pointer-types-discards-qualifiers"
#endif
    ret_val = dbm_open(file,
                       open_flags,
#ifdef __linux__
                       (int)
#endif
                           file_mode);
#pragma GCC diagnostic pop

    if(ret_val == NULL)
    {
        // TODO: what?
    }

    return ret_val;
}

#pragma GCC diagnostic pop

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

int p101_dbm_store(const struct p101_env *env, struct p101_error *err, DBM *db, datum key, datum content, int store_mode)
{
    int ret_val;

    P101_TRACE(env);
    errno   = 0;
    ret_val = dbm_store(db, key, content, store_mode);

    if(ret_val < 0)
    {
        // TODO: what?
    }

    return ret_val;
}

#pragma GCC diagnostic pop
