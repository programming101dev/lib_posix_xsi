#ifndef LIBP101_POSIX_XSI_SYS_P101_SHM_H
#define LIBP101_POSIX_XSI_SYS_P101_SHM_H

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
#include <sys/shm.h>

#ifdef __cplusplus
extern "C"
{
#endif

    void *p101_shmat(const struct p101_env *env, struct p101_error *err, int shmid, const void *shmaddr, int shmflg);
    int   p101_shmctl(const struct p101_env *env, struct p101_error *err, int shmid, int cmd, struct shmid_ds *buf);
    int   p101_shmdt(const struct p101_env *env, struct p101_error *err, const void *shmaddr);
    int   p101_shmget(const struct p101_env *env, struct p101_error *err, key_t key, size_t size, int shmflg);

#ifdef __cplusplus
}
#endif

#endif    // LIBP101_POSIX_XSI_SYS_P101_SHM_H
