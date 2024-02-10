#ifndef LIBP101_POSIX_XSI_P101_UNISTD_H
#define LIBP101_POSIX_XSI_P101_UNISTD_H

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
#include <sys/types.h>

#ifdef __cplusplus
extern "C"
{
#endif

    char *p101_crypt(const struct p101_env *env, struct p101_error *err, const char *key, const char *salt);
    long  p101_gethostid(const struct p101_env *env);
    int   p101_lockf(const struct p101_env *env, struct p101_error *err, int fildes, int function, off_t size);
    int   p101_nice(const struct p101_env *env, struct p101_error *err, int value);
    int   p101_setregid(const struct p101_env *env, struct p101_error *err, gid_t rgid, gid_t egid);
    int   p101_setreuid(const struct p101_env *env, struct p101_error *err, uid_t ruid, uid_t euid);
    void  p101_swab(const struct p101_env *env, const void *restrict src, void *restrict dest, ssize_t nbytes);
    void  p101_sync(const struct p101_env *env);

#ifdef __cplusplus
}
#endif

// Not on FreeBSD
// void p101_encrypt(const struct p101_env *env, struct p101_error *err, char block[64], int edflag);

#endif    // LIBP101_POSIX_XSI_P101_UNISTD_H
