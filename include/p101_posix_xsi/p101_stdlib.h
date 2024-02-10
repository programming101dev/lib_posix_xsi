#ifndef LIBP101_POSIX_XSI_P101_STDLIB_H
#define LIBP101_POSIX_XSI_P101_STDLIB_H

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

#include <p101_env/env.h>

#ifdef __cplusplus
extern "C"
{
#endif

    long            p101_a64l(const struct p101_env *env, const char *s);
    int             p101_grantpt(const struct p101_env *env, struct p101_error *err, int fildes);
    char           *p101_initstate(const struct p101_env *env, struct p101_error *err, unsigned seed, char *state, size_t size);
    char           *p101_l64a(const struct p101_env *env, long value);
    int             p101_posix_openpt(const struct p101_env *env, struct p101_error *err, int oflag);
    char           *p101_ptsname(const struct p101_env *env, struct p101_error *err, int fildes);
    int             p101_putenv(const struct p101_env *env, struct p101_error *err, char *string);
    char           *p101_realpath(const struct p101_env *env, struct p101_error *err, const char *restrict file_name, char *restrict resolved_name);
    unsigned short *p101_seed48(const struct p101_env *env, unsigned short seed16v[3]);
    char           *p101_setstate(const struct p101_env *env, struct p101_error *err, char *state);
    void            p101_srand48(const struct p101_env *env, long seedval);
    void            p101_srandom(const struct p101_env *env, unsigned seed);
    int             p101_unlockpt(const struct p101_env *env, struct p101_error *err, int fildes);

#ifdef __cplusplus
}
#endif

// Not on FreeBSD
// void p101_setkey(const struct p101_env *env, struct p101_error *err, const char *key);

// obsolete
// double p101_drand48(const struct p101_env *env);
// double p101_erand48(const struct p101_env *env, unsigned short xsubi[3]);
// long p101_jrand48(const struct p101_env *env, unsigned short xsubi[3]);
// void p101_lcong48(const struct p101_env *env, unsigned short param[7]);
// long p101_lrand48(const struct p101_env *env);
// long p101_mrand48(const struct p101_env *env);
// long p101_nrand48(const struct p101_env *env, unsigned short xsubi[3]);

// unsafe
// long p101_random(const struct p101_env *env);

#endif    // LIBP101_POSIX_XSI_P101_STDLIB_H
