#ifndef _SYS_RESOURCE_H
#define _SYS_RESOURCE_H

#include <sys/time.h>

#define RLIMIT_CPU     0
#define RLIMIT_FSIZE   1
#define RLIMIT_DATA    2
#define RLIMIT_STACK   3
#define RLIMIT_CORE    4
#define RLIMIT_NOFILE  5
#define RLIMIT_AS      6
#define RLIM_INFINITY  (~0UL)
#define RUSAGE_SELF     0
#define RUSAGE_CHILDREN -1

typedef unsigned long rlim_t;

struct rlimit {
    rlim_t rlim_cur;
    rlim_t rlim_max;
};

struct rusage {
    struct timeval ru_utime;
    struct timeval ru_stime;
    long ru_maxrss;
    long ru_ixrss, ru_idrss, ru_isrss;
    long ru_minflt, ru_majflt;
    long ru_nswap, ru_inblock, ru_oublock;
    long ru_msgsnd, ru_msgrcv;
    long ru_nsignals, ru_nvcsw, ru_nivcsw;
};

static inline int getrlimit(int r, struct rlimit *l) { (void)r; if(l){l->rlim_cur=RLIM_INFINITY;l->rlim_max=RLIM_INFINITY;} return 0; }
static inline int setrlimit(int r, const struct rlimit *l) { (void)r; (void)l; return -1; }
static inline int getrusage(int who, struct rusage *u) { (void)who; if(u) __builtin_memset(u,0,sizeof(*u)); return 0; }
static inline int getpriority(int w, int id) { (void)w; (void)id; return 0; }
static inline int setpriority(int w, int id, int p) { (void)w; (void)id; (void)p; return -1; }

#endif
