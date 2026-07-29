#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <math.h>
#include <p101_env/env.h>
#include <p101_error/error.h>
#include <p101_posix_xsi/p101_dirent.h>
#include <p101_posix_xsi/p101_ftw.h>
#include <p101_posix_xsi/p101_math.h>
#include <p101_posix_xsi/p101_ndbm.h>
#include <p101_posix_xsi/p101_search.h>
#include <p101_posix_xsi/p101_stdlib.h>
#include <p101_posix_xsi/p101_strings.h>
#include <p101_posix_xsi/p101_time.h>
#include <p101_posix_xsi/sys/p101_sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static int failures;

#define EXPECT(condition)                                                                                                                                                                                                                                          \
    do                                                                                                                                                                                                                                                             \
    {                                                                                                                                                                                                                                                              \
        if(!(condition))                                                                                                                                                                                                                                           \
        {                                                                                                                                                                                                                                                          \
            fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #condition);                                                                                                                                                                                   \
            failures++;                                                                                                                                                                                                                                            \
        }                                                                                                                                                                                                                                                          \
    } while(0)

struct event_counts
{
    int enters;
    int exits;
    int allocations;
    int frees;
};

struct fault_state
{
    const char *target;
    int         checks;
};

static void observe_calls(const struct p101_env *env, p101_env_call_event event, const char *call_name, const char *arguments, const char *result, const char *file_name, const char *function_name, int line_number, void *user_data)
{
    struct event_counts *counts;

    (void)env;
    (void)call_name;
    (void)arguments;
    (void)result;
    (void)file_name;
    (void)function_name;
    (void)line_number;
    counts = user_data;
    if(event == P101_ENV_CALL_ENTER)
    {
        counts->enters++;
    }
    else
    {
        counts->exits++;
    }
}

static void observe_allocations(const struct p101_env *env, p101_env_alloc_event event, const void *ptr, const void *new_ptr, size_t size, const char *file_name, const char *function_name, int line_number, void *user_data)
{
    struct event_counts *counts;

    (void)env;
    (void)ptr;
    (void)new_ptr;
    (void)size;
    (void)file_name;
    (void)function_name;
    (void)line_number;
    counts = user_data;
    if(event == P101_ENV_ALLOC_ALLOC)
    {
        counts->allocations++;
    }
    else if(event == P101_ENV_ALLOC_FREE)
    {
        counts->frees++;
    }
}

static int fail_named_call(const struct p101_env *env, const char *call_name, void *user_data)
{
    struct fault_state *state;

    (void)env;
    state = user_data;
    state->checks++;
    return (strcmp(call_name, state->target) == 0) ? ENOMEM : 0;
}

static int stop_walk(const char *path, const struct stat *status, int type, struct FTW *walk)
{
    (void)path;
    (void)status;
    (void)type;
    (void)walk;
    errno = EACCES;
    return -1;
}

static int stop_ftw_walk(const char *path, const struct stat *status, int type)
{
    (void)path;
    (void)status;
    (void)type;
    errno = EACCES;
    return -1;
}

static int compare_ints(const void *left, const void *right)
{
    const int *left_value;
    const int *right_value;

    left_value  = left;
    right_value = right;
    return (*left_value > *right_value) - (*left_value < *right_value);
}

static void test_status_contracts(struct p101_env *env, struct p101_error *err)
{
    int       values[] = {1, 3, 5};
    int       key      = 3;
    size_t    count    = sizeof(values) / sizeof(values[0]);
    struct tm parsed   = {0};
    char     *end;

    EXPECT(p101_nftw(env, err, ".", stop_walk, 4, FTW_PHYS) == -1);
    EXPECT(p101_error_has_no_error(err));
    EXPECT(p101_ftw(env, err, ".", stop_ftw_walk, 4) == -1);
    EXPECT(p101_error_has_no_error(err));

    EXPECT(p101_lfind(env, &key, values, &count, sizeof(values[0]), compare_ints) == &values[1]);

    end = p101_strptime(env, "2026-07-28 remainder", "%Y-%m-%d", &parsed);
    EXPECT(end != NULL);
    EXPECT(end != NULL && strcmp(end, " remainder") == 0);
    EXPECT(parsed.tm_year == 126);
    EXPECT(parsed.tm_mon == 6);
    EXPECT(parsed.tm_mday == 28);
}

static void test_math_errors(struct p101_env *env, struct p101_error *err)
{
    double result;

    result = p101_y0(env, err, -1.0);
    EXPECT(isnan(result));
    EXPECT(p101_error_is_errno(err, EDOM));
    p101_error_reset(err);

    result = p101_y0(env, err, 0.0);
    EXPECT(isinf(result));
    EXPECT(p101_error_is_errno(err, ERANGE));
    p101_error_reset(err);

    result = p101_j0(env, err, 0.0);
    EXPECT(result == 1.0);
    EXPECT(p101_error_has_no_error(err));
}

static void test_semctl_contract(struct p101_env *env, struct p101_error *err)
{
    union p101_semun argument = {0};

    EXPECT(p101_semctl(env, err, -1, 0, SETVAL) == -1);
    EXPECT(p101_error_is_errno(err, EINVAL));
    p101_error_reset(err);

    EXPECT(p101_semctl_arg(env, err, -1, 0, GETVAL, argument) == -1);
    EXPECT(p101_error_is_errno(err, EINVAL));
    p101_error_reset(err);
}

static void remove_db_files(const char *base)
{
    static const char *suffixes[] = {"", ".db", ".dir", ".pag"};
    char               path[512];
    size_t             index;

    for(index = 0; index < sizeof(suffixes) / sizeof(suffixes[0]); index++)
    {
        int written;

        written = snprintf(path, sizeof(path), "%s%s", base, suffixes[index]);
        if(written > 0 && (size_t)written < sizeof(path))
        {
            (void)unlink(path);
        }
    }
}

static void test_ndbm(struct p101_env *env, struct p101_error *err)
{
    char  directory[] = "/tmp/p101-posix-xsi-test.XXXXXX";
    char  path[512];
    char  key_text[]   = "key";
    char  value_text[] = "value";
    datum key          = {key_text, sizeof(key_text) - 1U};
    datum value        = {value_text, sizeof(value_text) - 1U};
    datum fetched;
    DBM  *database;
    int   written;

    if(mkdtemp(directory) == NULL)
    {
        EXPECT(0);
        return;
    }

    written = snprintf(path, sizeof(path), "%s/data", directory);
    EXPECT(written > 0 && (size_t)written < sizeof(path));
    if(written <= 0 || (size_t)written >= sizeof(path))
    {
        (void)rmdir(directory);
        return;
    }

    database = p101_dbm_open(env, err, path, O_RDWR | O_CREAT, 0600);
    EXPECT(database != NULL);
    EXPECT(p101_error_has_no_error(err));
    if(database != NULL)
    {
        EXPECT(p101_dbm_store(env, err, database, key, value, DBM_REPLACE) == 0);
        EXPECT(p101_error_has_no_error(err));

        fetched = p101_dbm_fetch(env, err, database, key);
        EXPECT(fetched.dptr != NULL);
        EXPECT(p101_error_has_no_error(err));
        EXPECT(fetched.dptr != NULL && fetched.dsize == value.dsize);
        EXPECT(fetched.dptr != NULL && memcmp(fetched.dptr, value.dptr, value.dsize) == 0);

        key.dptr  = "missing";
        key.dsize = sizeof("missing") - 1U;
        fetched   = p101_dbm_fetch(env, err, database, key);
        EXPECT(fetched.dptr == NULL);
        EXPECT(p101_error_has_no_error(err));

        p101_dbm_clearerr(env, database);
        EXPECT(p101_dbm_error(env, database) == 0);
        p101_dbm_close(env, database);
    }
    else
    {
        p101_error_reset(err);
    }

    remove_db_files(path);
    (void)rmdir(directory);
}

static void test_telldir(struct p101_env *env, struct p101_error *err)
{
    DIR *directory;

    directory = opendir(".");
    EXPECT(directory != NULL);
    if(directory == NULL)
    {
        return;
    }

    EXPECT(p101_telldir(env, err, directory) >= 0L);
    EXPECT(p101_error_has_no_error(err));
    (void)closedir(directory);
}

static void test_realpath_events(struct p101_env *env, struct p101_error *err, struct event_counts *counts)
{
    char *resolved;

    resolved = p101_realpath(env, err, ".", NULL);
    EXPECT(resolved != NULL);
    EXPECT(p101_error_has_no_error(err));
    EXPECT(counts->allocations == 1);
    if(resolved != NULL)
    {
        P101_TRACK_FREE(env, resolved);
        free(resolved);
    }
    EXPECT(counts->frees == 1);
}

static void test_faults_and_balanced_trace(struct p101_env *env, struct p101_error *err, struct event_counts *counts)
{
    struct fault_state fault = {"y0", 0};
    double             result;

    counts->enters = 0;
    counts->exits  = 0;
    p101_env_set_fault_injector(env, fail_named_call, &fault);
    p101_env_set_call_observer(env, observe_calls, counts);

    result = p101_y0(env, err, 1.0);
    EXPECT(isnan(result));
    EXPECT(p101_error_is_errno(err, ENOMEM));
    EXPECT(fault.checks == 1);
    EXPECT(counts->enters == 1);
    EXPECT(counts->enters == counts->exits);
    p101_error_reset(err);

    EXPECT(p101_ffs(env, 8) == 4);
    EXPECT(counts->enters == counts->exits);
    p101_env_set_call_observer(env, NULL, NULL);
    p101_env_set_fault_injector(env, NULL, NULL);
}

int main(void)
{
    struct event_counts counts = {0};
    struct p101_error  *err;
    struct p101_env    *env;

    err = p101_error_create(false);
    if(err == NULL)
    {
        return EXIT_FAILURE;
    }
    env = p101_env_create(err, NULL);
    if(env == NULL)
    {
        p101_error_destroy(err);
        return EXIT_FAILURE;
    }

    test_status_contracts(env, err);
    test_math_errors(env, err);
    test_semctl_contract(env, err);
    test_ndbm(env, err);
    test_telldir(env, err);

    p101_env_set_alloc_observer(env, observe_allocations, &counts);
    test_realpath_events(env, err, &counts);
    p101_env_set_alloc_observer(env, NULL, NULL);

    test_faults_and_balanced_trace(env, err, &counts);

    p101_env_destroy(env);
    p101_error_destroy(err);
    return (failures == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
