#ifndef _GRP_H
#define _GRP_H

#include <sys/types.h>

struct group {
    char *gr_name;
    char *gr_passwd;
    gid_t gr_gid;
    char **gr_mem;
};

static inline struct group *getgrgid(gid_t g) { (void)g; return (void*)0; }
static inline struct group *getgrnam(const char *n) { (void)n; return (void*)0; }
static inline void setgrent(void) {}
static inline void endgrent(void) {}
static inline struct group *getgrent(void) { return (void*)0; }

#endif
