#include <p101_posix_xsi/p101_dirent.h>
#include <p101_posix_xsi/p101_fmtmsg.h>
#include <p101_posix_xsi/p101_ftw.h>
#include <p101_posix_xsi/p101_libgen.h>
#include <p101_posix_xsi/p101_math.h>
#include <p101_posix_xsi/p101_ndbm.h>
#include <p101_posix_xsi/p101_search.h>
#include <p101_posix_xsi/p101_signal.h>
#include <p101_posix_xsi/p101_stdlib.h>
#include <p101_posix_xsi/p101_string.h>
#include <p101_posix_xsi/p101_strings.h>
#include <p101_posix_xsi/p101_syslog.h>
#include <p101_posix_xsi/p101_time.h>
#include <p101_posix_xsi/p101_unistd.h>
#include <p101_posix_xsi/p101_utmpx.h>
#include <p101_posix_xsi/p101_wchar.h>
#include <p101_posix_xsi/sys/p101_ipc.h>
#include <p101_posix_xsi/sys/p101_mman.h>
#include <p101_posix_xsi/sys/p101_msg.h>
#include <p101_posix_xsi/sys/p101_resource.h>
#include <p101_posix_xsi/sys/p101_sem.h>
#include <p101_posix_xsi/sys/p101_shm.h>
#include <p101_posix_xsi/sys/p101_stat.h>
#include <p101_posix_xsi/sys/p101_uio.h>

int main()
{
    union p101_semun argument{};
    int (*typed_semctl)(const p101_env *, p101_error *, int, int, int, p101_semun);

    typed_semctl = p101_semctl_arg;
    (void)argument;
    (void)typed_semctl;
    return 0;
}
