#ifndef LIBP101_POSIX_XSI_P101_UTMPX_H
#define LIBP101_POSIX_XSI_P101_UTMPX_H

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

    void          p101_endutxent(const struct p101_env *env);
    struct utmpx *p101_getutxent(const struct p101_env *env);
    struct utmpx *p101_getutxid(const struct p101_env *env, const struct utmpx *id);
    struct utmpx *p101_getutxline(const struct p101_env *env, const struct utmpx *line);
    struct utmpx *p101_pututxline(const struct p101_env *env, struct p101_error *err, const struct utmpx *utmpx);
    void          p101_setutxent(const struct p101_env *env);

#ifdef __cplusplus
}
#endif

#endif    // LIBP101_POSIX_XSI_P101_UTMPX_H
