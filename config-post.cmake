# Platform-specific link dependencies. This file is included by the shared
# CMakeLists.txt after project(), when CMAKE_SYSTEM_NAME is reliable.

# macOS and FreeBSD provide these through their base system libraries. On Linux,
# crypt is in libcrypt and the ndbm-compatible dbm_* API is commonly provided
# by gdbm_compat over gdbm.
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    list(APPEND p101_posix_xsi_LINK_LIBRARIES crypt gdbm_compat gdbm)
endif()
