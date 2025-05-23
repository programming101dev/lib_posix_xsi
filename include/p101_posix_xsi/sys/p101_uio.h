#ifndef LIBP101_POSIX_XSI_SYS_P101_UIO_H
#define LIBP101_POSIX_XSI_SYS_P101_UIO_H

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
#include <sys/uio.h>

#ifdef __cplusplus
extern "C"
{
#endif

    ssize_t p101_readv(const struct p101_env *env, struct p101_error *err, int fildes, const struct iovec *iov, int iovcnt);
    ssize_t p101_writev(const struct p101_env *env, struct p101_error *err, int fildes, const struct iovec *iov, int iovcnt);

#ifdef __cplusplus
}
#endif

#endif    // LIBP101_POSIX_XSI_SYS_P101_UIO_H
