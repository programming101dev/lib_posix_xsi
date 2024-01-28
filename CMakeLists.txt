cmake_minimum_required(VERSION 3.10)
project(p101_posix_xsi
    VERSION 0.0.1
    DESCRIPTION ""
    LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Source files for the library
set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/dirent.c
    ${CMAKE_SOURCE_DIR}/src/fmtmsg.c
    ${CMAKE_SOURCE_DIR}/src/ftw.c
    ${CMAKE_SOURCE_DIR}/src/grp.c
    ${CMAKE_SOURCE_DIR}/src/libgen.c
    ${CMAKE_SOURCE_DIR}/src/math.c
    ${CMAKE_SOURCE_DIR}/src/ndbm.c
    ${CMAKE_SOURCE_DIR}/src/pwd.c
    ${CMAKE_SOURCE_DIR}/src/search.c
    ${CMAKE_SOURCE_DIR}/src/signal.c
    ${CMAKE_SOURCE_DIR}/src/stdlib.c
    ${CMAKE_SOURCE_DIR}/src/string.c
    ${CMAKE_SOURCE_DIR}/src/strings.c
    ${CMAKE_SOURCE_DIR}/src/syslog.c
    ${CMAKE_SOURCE_DIR}/src/time.c
    ${CMAKE_SOURCE_DIR}/src/unistd.c
    ${CMAKE_SOURCE_DIR}/src/utmpx.c
    ${CMAKE_SOURCE_DIR}/src/wchar.c
)

# Define the list of header files to install
set(HEADER_LIST
    ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/p101_dirent.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/p101_fmtmsg.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/p101_ftw.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/p101_grp.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/p101_libgen.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/p101_math.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/p101_ndbm.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/p101_pwd.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/p101_search.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/p101_signal.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/p101_stdlib.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/p101_string.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/p101_strings.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/p101_syslog.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/p101_time.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/p101_unistd.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/p101_utmpx.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/p101_wchar.h
)

set(HEADER_LIST_SYS
    ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/sys/p101_ipc.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/sys/p101_mman.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/sys/p101_msg.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/sys/p101_resource.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/sys/p101_sem.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/sys/p101_shm.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/sys/p101_stat.h
    ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/sys/p101_time.h
)

# Build the shared library
add_library(p101_posix_xsi SHARED ${SOURCES})
target_include_directories(p101_posix_xsi PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(p101_posix_xsi PRIVATE /usr/local/include)

# Extract the compiler name without the path
get_filename_component(COMPILER_NAME "${CMAKE_C_COMPILER}" NAME)

function(split_string_into_list _input_string _output_list)
    string(REGEX REPLACE "[ ]+" ";" _split_list "${_input_string}")
    set(${_output_list} ${_split_list} PARENT_SCOPE)
endfunction()

# Import analyzer_flags.txt
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/.flags/${COMPILER_NAME}/analyzer_flags.txt" ANALYZER_FLAGS_STRING)
split_string_into_list("${ANALYZER_FLAGS_STRING}" ANALYZER_FLAGS_LIST)

# Import debug_flags.txt
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/.flags/${COMPILER_NAME}/debug_flags.txt" DEBUG_FLAGS_STRING)
split_string_into_list("${DEBUG_FLAGS_STRING}" DEBUG_FLAGS_LIST)

# Import instrumentation_flags.txt
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/.flags/${COMPILER_NAME}/instrumentation_flags.txt" INSTRUMENTATION_FLAGS_STRING)
split_string_into_list("${INSTRUMENTATION_FLAGS_STRING}" INSTRUMENTATION_FLAGS_LIST)

# Import optimization_flags.txt
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/.flags/${COMPILER_NAME}/optimization_flags.txt" OPTIMIZATION_FLAGS_STRING)
split_string_into_list("${OPTIMIZATION_FLAGS_STRING}" OPTIMIZATION_FLAGS_LIST)

# Import warning_flags.txt
file(STRINGS "${CMAKE_CURRENT_SOURCE_DIR}/.flags/${COMPILER_NAME}/warning_flags.txt" WARNING_FLAGS_STRING)
split_string_into_list("${WARNING_FLAGS_STRING}" WARNING_FLAGS_LIST)

# Check if the system uses 64-bit libraries
get_property(LIB64 GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS)

# Set the library suffix based on whether it's 64-bit or not
if ("${LIB64}" STREQUAL "TRUE")
    set(LIBSUFFIX 64)
else()
    set(LIBSUFFIX "")
endif()

target_link_directories(p101_posix_xsi PRIVATE /usr/local/lib${LIBSUFFIX})

# Enable sanitizer checks
target_link_libraries(p101_posix_xsi PRIVATE ${SANITIZER_FLAGS_STRING})

# Link libraries
target_link_libraries(p101_posix_xsi PRIVATE p101_error)
target_link_libraries(p101_posix_xsi PRIVATE p101_env)
target_link_libraries(p101_posix_xsi PRIVATE p101_c)

# Common compiler flags
set(STANDARD_FLAGS
    -D_POSIX_C_SOURCE=200809L
    -D_XOPEN_SOURCE=700
    -D_GNU_SOURCE
    -D_DARWIN_C_SOURCE
    -Werror
)

# Set compiler flags for the target
target_compile_options(p101_posix_xsi PRIVATE
        ${STANDARD_FLAGS}
        ${ANALYZER_FLAGS_LIST}
        ${DEBUG_FLAGS_LIST}
        ${INSTRUMENTATION_FLAGS_LIST}
        ${OPTIMIZATION_FLAGS_LIST}
        ${WARNING_FLAGS_LIST}
)

if (NOT DEFINED CLANG_FORMAT_NAME)
    set(CLANG_FORMAT_NAME "clang-format")
endif()

if (NOT DEFINED CLANG_TIDY_NAME)
    set(CLANG_TIDY_NAME "clang-tidy")
endif()

if (NOT DEFINED CPPCHECK_NAME)
    set(CPPCHECK_NAME "cppcheck")
endif()

find_program(CLANG_FORMAT NAMES ${CLANG_FORMAT_NAME} REQUIRED)
find_program(CLANG_TIDY NAMES ${CLANG_TIDY_NAME} REQUIRED)
find_program(CPPCHECK NAMES ${CPPCHECK_NAME} REQUIRED)

# Format source files using clang-format
add_custom_target(format
    COMMAND ${CLANG_FORMAT} --style=file -i ${SOURCES} ${HEADER_LIST}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running clang-format"
)

# Lint source files using clang-tidy
add_custom_target(lint
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND ${CLANG_TIDY} ${SOURCES} ${HEADER_LIST} -quiet --warnings-as-errors='*' -checks=*,-llvmlibc-restrict-system-libc-headers,-altera-struct-pack-align,-readability-identifier-length,-altera-unroll-loops,-cppcoreguidelines-init-variables,-cert-err33-c,-modernize-macro-to-enum,-bugprone-easily-swappable-parameters,-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling,-altera-id-dependent-backward-branch,-concurrency-mt-unsafe,-misc-unused-parameters,-hicpp-signed-bitwise,-google-readability-todo,-cert-msc30-c,-cert-msc50-cpp,-readability-function-cognitive-complexity,-clang-analyzer-security.insecureAPI.strcpy,-cert-env33-c,-android-cloexec-accept,-clang-analyzer-security.insecureAPI.rand,-misc-include-cleaner,-llvm-header-guard -- ${CMAKE_C_FLAGS} ${STANDARD_FLAGS} -I${CMAKE_SOURCE_DIR}/include -I/usr/local/include
    COMMENT "Running clang-tidy"
)

# Add a custom target for cppcheck
add_custom_target(cppcheck
    COMMAND ${CPPCHECK} --error-exitcode=1 --force --quiet --inline-suppr --library=posix --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction --suppress=getgrentCalled --suppress=getpwentCalled --suppress=cryptCalled --suppress=constParameterPointer --suppress=constParameter --suppress=unmatchedSuppression --suppress=checkersReport -I${CMAKE_SOURCE_DIR}/include -I/usr/local/include ${SOURCES} ${HEADER_LIST}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running cppcheck"
)

# Check if CMAKE_C_COMPILER starts with "clang"
if (CMAKE_C_COMPILER MATCHES ".*/clang.*")
    # Add a custom target for clang --analyze
    add_custom_target(analysis
        COMMAND ${CMAKE_C_COMPILER} --analyze --analyzer-output text -Xclang -analyzer-checker=core --analyze -Xclang -analyzer-checker=deadcode -Xclang -analyzer-checker=security -Xclang -analyzer-disable-checker=security.insecureAPI.DeprecatedOrUnsafeBufferHandling -Xclang -analyzer-checker=unix -Xclang -analyzer-checker=unix ${CMAKE_C_FLAGS} ${STANDARD_FLAGS} -I${CMAKE_SOURCE_DIR}/include -I/usr/local/include ${SOURCES} ${HEADER_LIST}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        COMMENT "Running clang --analyze"
    )

    # Add a custom command to delete .gch files after the analysis
    add_custom_command(
        TARGET analysis POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/*.gch ${CMAKE_SOURCE_DIR}/include/p101_posix_xsi/sys/*.gch
        COMMENT "Removing .gch files"
    )

    # Add dependencies including 'analysis' for Clang compiler
    add_custom_target(strict
        DEPENDS p101_posix_xsi analysis lint cppcheck
        COMMENT "Running code analysis tools"
    )
else()
    # Add dependencies without 'analysis' for other compilers
    add_custom_target(strict
        DEPENDS p101_posix_xsi lint cppcheck
        COMMENT "Running code analysis tools"
    )
endif()

add_dependencies(p101_posix_xsi format)

# Set the default target to be 'strict'
add_custom_target(default_target DEPENDS strict)

# Define the installation directory for libraries
set(INSTALL_LIB_DIR lib${LIBSUFFIX} CACHE PATH "Installation directory for libraries")
mark_as_advanced(INSTALL_LIB_DIR)

set_target_properties(p101_posix_xsi PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR})

# Install the library target
install(TARGETS p101_posix_xsi
    LIBRARY DESTINATION ${INSTALL_LIB_DIR}
    COMPONENT library
    NAMELINK_COMPONENT development
)

# Install header files
install(FILES ${HEADER_LIST}
    DESTINATION include/p101_posix_xsi
)

install(FILES ${HEADER_LIST_SYS}
    DESTINATION include/p101_posix_xsi/sys
)
