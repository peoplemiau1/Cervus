#ifndef _SPAWN_H
#define _SPAWN_H

#include <sys/types.h>
#include <signal.h>

typedef struct { int __dummy; } posix_spawnattr_t;
typedef struct { int __dummy; } posix_spawn_file_actions_t;

static inline int posix_spawn(pid_t *pid, const char *path,
    const posix_spawn_file_actions_t *fa, const posix_spawnattr_t *sa,
    char *const argv[], char *const envp[]) {
    (void)pid;(void)path;(void)fa;(void)sa;(void)argv;(void)envp;
    return -1;
}

static inline int posix_spawnp(pid_t *pid, const char *file,
    const posix_spawn_file_actions_t *fa, const posix_spawnattr_t *sa,
    char *const argv[], char *const envp[]) {
    (void)pid;(void)file;(void)fa;(void)sa;(void)argv;(void)envp;
    return -1;
}

static inline int posix_spawn_file_actions_init(posix_spawn_file_actions_t *fa) { (void)fa; return 0; }
static inline int posix_spawn_file_actions_destroy(posix_spawn_file_actions_t *fa) { (void)fa; return 0; }
static inline int posix_spawn_file_actions_adddup2(posix_spawn_file_actions_t *fa, int o, int n) { (void)fa;(void)o;(void)n; return 0; }
static inline int posix_spawn_file_actions_addclose(posix_spawn_file_actions_t *fa, int fd) { (void)fa;(void)fd; return 0; }
static inline int posix_spawn_file_actions_addopen(posix_spawn_file_actions_t *fa, int fd, const char *p, int f, mode_t m) { (void)fa;(void)fd;(void)p;(void)f;(void)m; return 0; }
static inline int posix_spawnattr_init(posix_spawnattr_t *sa) { (void)sa; return 0; }
static inline int posix_spawnattr_destroy(posix_spawnattr_t *sa) { (void)sa; return 0; }
static inline int posix_spawnattr_setflags(posix_spawnattr_t *sa, short f) { (void)sa;(void)f; return 0; }
static inline int posix_spawnattr_setsigmask(posix_spawnattr_t *sa, const sigset_t *s) { (void)sa;(void)s; return 0; }
static inline int posix_spawnattr_setsigdefault(posix_spawnattr_t *sa, const sigset_t *s) { (void)sa;(void)s; return 0; }

#define POSIX_SPAWN_RESETIDS      0x01
#define POSIX_SPAWN_SETPGROUP     0x02
#define POSIX_SPAWN_SETSIGDEF     0x04
#define POSIX_SPAWN_SETSIGMASK    0x08
#define POSIX_SPAWN_SETSCHEDPARAM 0x10
#define POSIX_SPAWN_SETSCHEDULER  0x20

#endif
