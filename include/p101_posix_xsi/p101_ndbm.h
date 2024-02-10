#ifndef LIBP101_POSIX_XSI_P101_NDBM_H
#define LIBP101_POSIX_XSI_P101_NDBM_H

/*
 * Copyright 2022-2024 D'Arcy Smith.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <ndbm.h>
#include <p101_env/env.h>
#include <sys/stat.h>

#ifdef __cplusplus
extern "C"
{
#endif

    int   p101_dbm_clearerr(const struct p101_env *env, struct p101_error *err, DBM *db);
    void  p101_dbm_close(const struct p101_env *env, DBM *db);
    int   p101_dbm_delete(const struct p101_env *env, struct p101_error *err, DBM *db, datum key);
    int   p101_dbm_error(const struct p101_env *env, DBM *db);
    datum p101_dbm_fetch(const struct p101_env *env, struct p101_error *err, DBM *db, datum key);
    datum p101_dbm_firstkey(const struct p101_env *env, struct p101_error *err, DBM *db);
    datum p101_dbm_nextkey(const struct p101_env *env, struct p101_error *err, DBM *db);
    DBM  *p101_dbm_open(const struct p101_env *env, struct p101_error *err, const char *file, int open_flags, mode_t file_mode);
    int   p101_dbm_store(const struct p101_env *env, struct p101_error *err, DBM *db, datum key, datum content, int store_mode);

#ifdef __cplusplus
}
#endif

#endif    // LIBP101_POSIX_XSI_P101_NDBM_H
