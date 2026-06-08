#ifndef _PWD_H
#define _PWD_H

#include <sys/types.h>

struct passwd {
    char *pw_name;
    char *pw_passwd;
    uid_t pw_uid;
    gid_t pw_gid;
    char *pw_gecos;
    char *pw_dir;
    char *pw_shell;
};

static inline struct passwd *getpwuid(uid_t uid) { (void)uid; return (void*)0; }
static inline struct passwd *getpwnam(const char *n) { (void)n; return (void*)0; }
static inline int getpwuid_r(uid_t u, struct passwd *p, char *b, size_t bs, struct passwd **r) { (void)u;(void)p;(void)b;(void)bs; *r=0; return -1; }
static inline int getpwnam_r(const char *n, struct passwd *p, char *b, size_t bs, struct passwd **r) { (void)n;(void)p;(void)b;(void)bs; *r=0; return -1; }
static inline void setpwent(void) {}
static inline void endpwent(void) {}
static inline struct passwd *getpwent(void) { return (void*)0; }

#endif
