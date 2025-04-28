# Project metadata
set(PROJECT_NAME "p101_posix_xsi")
set(PROJECT_VERSION "0.0.1")
set(PROJECT_DESCRIPTION "POSIX utilities for Unix systems")
set(PROJECT_LANGUAGE "C")

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Common compiler flags
set(STANDARD_FLAGS
        -D_POSIX_C_SOURCE=200809L
        -D_XOPEN_SOURCE=700
        -D_DEFAULT_SOURCE
        #-D_GNU_SOURCE
        #-D_DARWIN_C_SOURCE
        #-D__BSD_VISIBLE
        -Werror
)

#if(CMAKE_C_COMPILER_ID STREQUAL "Clang")
#    if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
#        list(APPEND STANDARD_FLAGS -D_GNU_SOURCE)
#    endif()
#endif()

# Define library targets
set(LIBRARY_TARGETS p101_posix_xsi)

# Source files for the library
set(p101_posix_xsi_SOURCES
        src/dirent.c
        src/fmtmsg.c
        src/ftw.c
        src/libgen.c
        src/math.c
        src/ndbm.c
        src/search.c
        src/signal.c
        src/stdlib.c
        src/string.c
        src/strings.c
        src/syslog.c
        src/time.c
        src/unistd.c
        src/utmpx.c
        src/wchar.c
        src/sys/ipc.c
        src/sys/mman.c
        src/sys/msg.c
        src/sys/resource.c
        src/sys/sem.c
        src/sys/shm.c
        src/sys/stat.c
        src/sys/uio.c
)

# Header files for installation, maintaining subdirectory structure
set(p101_posix_xsi_HEADERS
        include/p101_posix_xsi/p101_dirent.h
        include/p101_posix_xsi/p101_fmtmsg.h
        include/p101_posix_xsi/p101_ftw.h
        include/p101_posix_xsi/p101_libgen.h
        include/p101_posix_xsi/p101_math.h
        include/p101_posix_xsi/p101_ndbm.h
        include/p101_posix_xsi/p101_search.h
        include/p101_posix_xsi/p101_signal.h
        include/p101_posix_xsi/p101_stdlib.h
        include/p101_posix_xsi/p101_string.h
        include/p101_posix_xsi/p101_strings.h
        include/p101_posix_xsi/p101_syslog.h
        include/p101_posix_xsi/p101_time.h
        include/p101_posix_xsi/p101_unistd.h
        include/p101_posix_xsi/p101_utmpx.h
        include/p101_posix_xsi/p101_wchar.h
        include/p101_posix_xsi/sys/p101_ipc.h
        include/p101_posix_xsi/sys/p101_mman.h
        include/p101_posix_xsi/sys/p101_msg.h
        include/p101_posix_xsi/sys/p101_resource.h
        include/p101_posix_xsi/sys/p101_sem.h
        include/p101_posix_xsi/sys/p101_shm.h
        include/p101_posix_xsi/sys/p101_stat.h
        include/p101_posix_xsi/sys/p101_uio.h
)

# Linked libraries required for this project
set(p101_posix_xsi_LINK_LIBRARIES
        p101_error
        p101_env
        p101_c
)
