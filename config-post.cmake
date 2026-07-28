# Platform-specific link dependencies. This file is included by the shared
# CMakeLists.txt after project(), when CMAKE_SYSTEM_NAME is reliable.

# macOS provides crypt() through its base system libraries. On Linux and
# FreeBSD, crypt() is in libcrypt. The ndbm-compatible dbm_* API is commonly
# provided by gdbm_compat over gdbm on Linux.
if(CMAKE_SYSTEM_NAME MATCHES "Linux|FreeBSD")
    list(APPEND p101_posix_xsi_LINK_LIBRARIES crypt)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    list(APPEND p101_posix_xsi_LINK_LIBRARIES gdbm_compat gdbm)
endif()
