#ifndef _SEMAPHORE_H
#define _SEMAPHORE_H

typedef struct { int __val; } sem_t;

#define SEM_FAILED ((sem_t*)-1)

static inline int sem_init(sem_t *s, int pshared, unsigned val) { (void)pshared; s->__val = val; return 0; }
static inline int sem_destroy(sem_t *s) { (void)s; return 0; }
static inline int sem_wait(sem_t *s) { s->__val--; return 0; }
static inline int sem_trywait(sem_t *s) { if (s->__val > 0) { s->__val--; return 0; } return -1; }
static inline int sem_post(sem_t *s) { s->__val++; return 0; }
static inline int sem_getvalue(sem_t *s, int *v) { *v = s->__val; return 0; }

#endif
