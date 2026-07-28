# lib_posix_xsi Repository Guide

Welcome to the `lib_posix_xsi` repository — POSIX XSI utilities, part of the Programming 101 C library collection. This guide will help you set up, build, and install the library.

## **Table of Contents**

1. [Cloning the Repository](#cloning-the-repository)
2. [Prerequisites](#prerequisites)
3. [Configuring the Build](#configuring-the-build)
4. [Building](#building)
5. [Testing](#testing)
6. [Installing](#installing)
7. [Adding or Removing Files](#adding-or-removing-files)

## **Cloning the Repository**

Clone the repository using the following command:

```bash
git clone https://github.com/programming101dev/lib_posix_xsi.git
```

Navigate to the cloned directory:

```bash
cd lib_posix_xsi
```

Ensure the scripts are executable:

```bash
chmod +x *.sh
```

## **Prerequisites**

To ensure you have all of the required tools installed, run:

```bash
./check-env.sh
```

If you are missing tools follow these [instructions](https://docs.google.com/document/d/1ZPqlPD1mie5iwJ2XAcNGz7WeA86dTLerFXs9sAuwCco/edit?usp=drive_link). If something still looks wrong, `./doctor.sh` reports what actually works on this machine for this project.

FreeBSD note: `p101_crypt()` needs the platform crypt library. The p101 setup
repo and CI install `libxcrypt`; if you maintain a FreeBSD machine by hand,
install that package before building this library.

## **Configuring the Build**

Tell CMake which compiler you want to use:

```bash
./change-compiler.sh -c <compiler>
```

To see the list of possible compilers:

```bash
cat supported_c_compilers.txt
```

Run it again any time to switch compilers; each compiler configures into its own build directory (e.g. `build-clang`, `build-gcc-15`).

## **Building**

To build the library run:

```bash
./build.sh
```

This compiles through the strict analysis pipeline: the clang-format check, clang-tidy, cppcheck, the Clang static analyzer, and hundreds of warnings under `-Werror`. `./build.sh -f` applies the formatter and tidy fixes in place.

## **Testing**

`./check.sh` is the one command to run before you submit: the format check, the strict build, the tests, and a short fuzz smoke run, with a single PASS/FAIL at the end.

The behavioral suite checks error-sentinel handling, XSI math errors, NDBM
storage, the typed `semctl` interface, allocation events, fault injection, and
balanced entry/exit tracing. It also compiles every public header as both C and
C++:

```bash
./test.sh
```

The bounded fuzz target exercises the string, path, date, and Bessel wrappers
with ASan and UBSan:

```bash
./fuzz.sh -t 30
```

## **Contract and Scope**

This is a curated wrapper library for XSI interfaces that are present on
Linux, FreeBSD, and macOS. It is not a claim that every interface in the XSI
option is wrapped. The public surface is grouped by the native headers:

- directories, file-tree walking, paths, search, strings, time, wide
  characters, logging, terminals, and legacy account records;
- XSI math and NDBM;
- IPC keys, message queues, semaphores, shared memory, memory synchronization,
  resource limits, special files, and vectored I/O.

Every wrapper emits a p101 call-entry and call-exit event. Wrappers with a
defined failure result accept `p101_error`, preserve the native return
convention, and participate in `p101_env` fault injection. Interfaces such as
`lfind`, `strptime`, and `dbm_clearerr` do not accept a fake error channel when
their native contract does not report one.

The event stream only sees calls made through these wrappers. It cannot observe
direct libc calls, third-party code, kernel work performed behind an interface,
or misuse that the native interface itself does not diagnose. The wrappers are
deterministic adapters around native behavior, not proofs of correctness.

### Ownership and state

`p101_realpath(env, err, path, NULL)` uses the extension supported by all three
target platforms. On success it emits an allocation event; release the returned
buffer with `p101_free` so the matching free is observable. A caller-supplied
buffer remains caller-owned.

`p101_semctl` is for commands with no fourth argument.
`p101_semctl_arg` takes the portable `union p101_semun` for `GETALL`, `SETALL`,
`SETVAL`, `IPC_STAT`, and `IPC_SET`. Splitting the API keeps the native
variadic-union ABI out of C++ call sites.

The wrappers do not add synchronization. Native interfaces that use process
global or static state—including `crypt`, `l64a`, `ptsname`, the random-state
family, syslog, utmpx, and the non-reentrant search table—retain those
limitations. `p101_crypt` is compatibility-only, returns static storage, is not
thread-safe, and must not be used for new password storage.

## **Installing**

To install the library run:

```bash
./install.sh
```

You may need to run it via sudo, or give the user account access to the install directories. `./uninstall.sh` removes it again.

## **Adding or Removing Files**

The `CMakeLists.txt` is fixed and shared across every repository — do not edit it. When you add or remove a source or header, edit the lists in `config.cmake` (`p101_posix_xsi_SOURCES`, `p101_posix_xsi_HEADERS`, and `p101_posix_xsi_LINK_LIBRARIES`), then re-configure and build:

```bash
./change-compiler.sh -c <compiler>
./build.sh
```
