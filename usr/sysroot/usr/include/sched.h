#ifndef _SCHED_H
#define _SCHED_H

#include <sys/types.h>

struct sched_param {
    int sched_priority;
};

#define SCHED_OTHER 0
#define SCHED_FIFO  1
#define SCHED_RR    2

typedef struct { unsigned long __bits[1]; } cpu_set_t;

int sched_yield(void);
static inline int sched_get_priority_max(int policy) { (void)policy; return 0; }
static inline int sched_get_priority_min(int policy) { (void)policy; return 0; }
static inline int sched_setscheduler(pid_t pid, int policy, const struct sched_param *p) { (void)pid;(void)policy;(void)p; return -1; }
static inline int sched_getscheduler(pid_t pid) { (void)pid; return SCHED_OTHER; }
static inline int sched_setparam(pid_t pid, const struct sched_param *p) { (void)pid;(void)p; return -1; }
static inline int sched_getparam(pid_t pid, struct sched_param *p) { (void)pid;(void)p; return -1; }
static inline int sched_setaffinity(pid_t pid, size_t size, const cpu_set_t *set) { (void)pid;(void)size;(void)set; return -1; }
static inline int sched_getaffinity(pid_t pid, size_t size, cpu_set_t *set) { (void)pid;(void)size;(void)set; return -1; }

#endif
