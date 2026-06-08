#ifndef _SYS_SELECT_H
#define _SYS_SELECT_H

#include <sys/types.h>
#include <sys/time.h>

#define FD_SETSIZE 64

typedef struct { unsigned long fds_bits[FD_SETSIZE / (8 * sizeof(unsigned long))]; } fd_set;

#define FD_ZERO(s)   do { unsigned long *_p = (s)->fds_bits; int _i; for(_i=0;_i<(int)(sizeof((s)->fds_bits)/sizeof(unsigned long));_i++) _p[_i]=0; } while(0)
#define FD_SET(d,s)  ((s)->fds_bits[(d)/(8*sizeof(unsigned long))] |= (1UL << ((d) % (8*sizeof(unsigned long)))))
#define FD_CLR(d,s)  ((s)->fds_bits[(d)/(8*sizeof(unsigned long))] &= ~(1UL << ((d) % (8*sizeof(unsigned long)))))
#define FD_ISSET(d,s) (((s)->fds_bits[(d)/(8*sizeof(unsigned long))] >> ((d) % (8*sizeof(unsigned long)))) & 1)

static inline int select(int nfds, fd_set *r, fd_set *w, fd_set *e, struct timeval *t) {
    (void)nfds; (void)r; (void)w; (void)e; (void)t;
    return -1;
}

#endif
