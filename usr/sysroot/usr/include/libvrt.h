#ifndef _LIBVRT_H
#define _LIBVRT_H

#include <setjmp.h>
#include <stdbool.h>
#include <stddef.h>

#define VRT_STACK_SIZE 16384
#define VRT_MAX_THREADS 16


typedef enum {
    VRT_FREE = 0,
    VRT_READY,
    VRT_RUNNING,
    VRT_BLOCKED
} vrt_state_t;


typedef struct {
    int         id;
    vrt_state_t state;
    jmp_buf     env;
    void       *stack_allocated; 
    char        name[32];
} vrt_thread_t;


typedef struct {
    int  data_val;
    bool has_data;
    int  reader_tid; 
    int  writer_tid; 
} vrt_chan_t;


void vrt_init(void);
int  vrt_spawn(const char *name, void (*func)(void *), void *arg);
void vrt_yield(void);
void vrt_exit(void) __attribute__((noreturn));


void vrt_chan_init(vrt_chan_t *chan);
void vrt_chan_send(vrt_chan_t *chan, int val);
int  vrt_chan_recv(vrt_chan_t *chan);


int  vrt_system(const char *command);

#endif
