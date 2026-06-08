#include <libvrt.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


#define JB_RBX 0
#define JB_RBP 1
#define JB_R12 2
#define JB_R13 3
#define JB_RSP 6
#define JB_RIP 7

typedef struct {
    vrt_thread_t threads[VRT_MAX_THREADS];
    int          current_id;
    int          active_count;
} vrt_sched_t;

static vrt_sched_t g_sched;


static void vrt_trampoline(void) {
    register void (*func)(void *) asm("r12");
    register void *arg            asm("r13");

    
    func(arg); 

    
    vrt_exit();
}


void vrt_init(void) {
    memset(&g_sched, 0, sizeof(g_sched));
    
    
    vrt_thread_t *main_t = &g_sched.threads[0];
    main_t->id = 0;
    main_t->state = VRT_RUNNING;
    strncpy(main_t->name, "main", sizeof(main_t->name) - 1);
    
    g_sched.current_id = 0;
    g_sched.active_count = 1;
}


int vrt_spawn(const char *name, void (*func)(void *), void *arg) {
    int slot = -1;
    for (int i = 0; i < VRT_MAX_THREADS; i++) {
        if (g_sched.threads[i].state == VRT_FREE) {
            slot = i;
            break;
        }
    }
    if (slot < 0) return -1;

    vrt_thread_t *t = &g_sched.threads[slot];
    memset(t, 0, sizeof(vrt_thread_t));

    
    t->stack_allocated = malloc(VRT_STACK_SIZE);
    if (!t->stack_allocated) return -1;

    
    uintptr_t stack_top = (uintptr_t)((char *)t->stack_allocated + VRT_STACK_SIZE);
    stack_top = stack_top & ~15ULL;

    
    uintptr_t *sp = (uintptr_t *)stack_top;
    *(--sp) = (uintptr_t)vrt_exit;

    
    t->env[JB_RSP] = (uintptr_t)sp;
    t->env[JB_RIP] = (uintptr_t)vrt_trampoline;
    t->env[JB_R12] = (uintptr_t)func; 
    t->env[JB_R13] = (uintptr_t)arg;  
    t->env[JB_RBP] = (uintptr_t)sp;

    t->id = slot;
    t->state = VRT_READY;
    strncpy(t->name, name, sizeof(t->name) - 1);

    g_sched.active_count++;
    return slot;
}


void vrt_yield(void) {
    int old_id = g_sched.current_id;
    
    
    int next_id = -1;
    for (int i = 1; i <= VRT_MAX_THREADS; i++) {
        int idx = (old_id + i) % VRT_MAX_THREADS;
        if (g_sched.threads[idx].state == VRT_READY) {
            next_id = idx;
            break;
        }
    }

    
    if (next_id < 0) {
        if (g_sched.threads[old_id].state == VRT_RUNNING) {
            return; 
        }
        
        printf("[libvrt] DEADLOCK: All threads are blocked!\n");
        exit(1);
    }

    
    if (g_sched.threads[old_id].state == VRT_RUNNING) {
        g_sched.threads[old_id].state = VRT_READY;
    }

    
    if (setjmp(g_sched.threads[old_id].env) == 0) {
        g_sched.current_id = next_id;
        g_sched.threads[next_id].state = VRT_RUNNING;
        longjmp(g_sched.threads[next_id].env, 1);
    }
}


void vrt_exit(void) {
    int id = g_sched.current_id;
    if (id == 0) {
        printf("[libvrt] Main thread cannot call vrt_exit directly!\n");
        exit(0);
    }

    vrt_thread_t *t = &g_sched.threads[id];
    t->state = VRT_FREE;
    free(t->stack_allocated);
    t->stack_allocated = NULL;
    
    g_sched.active_count--;

    
    vrt_yield();
    
    
    __builtin_unreachable();
}



void vrt_chan_init(vrt_chan_t *chan) {
    chan->data_val = 0;
    chan->has_data = false;
    chan->reader_tid = -1;
    chan->writer_tid = -1;
}


void vrt_chan_send(vrt_chan_t *chan, int val) {
    int my_id = g_sched.current_id;

    
    while (chan->has_data) {
        g_sched.threads[my_id].state = VRT_BLOCKED;
        chan->writer_tid = my_id;
        vrt_yield();
    }

    
    chan->data_val = val;
    chan->has_data = true;

    
    if (chan->reader_tid != -1) {
        g_sched.threads[chan->reader_tid].state = VRT_READY;
        chan->reader_tid = -1;
    }

    
    vrt_yield();
}


int vrt_chan_recv(vrt_chan_t *chan) {
    int my_id = g_sched.current_id;

    
    while (!chan->has_data) {
        g_sched.threads[my_id].state = VRT_BLOCKED;
        chan->reader_tid = my_id;
        vrt_yield();
    }

    int val = chan->data_val;
    chan->has_data = false;

    
    if (chan->writer_tid != -1) {
        g_sched.threads[chan->writer_tid].state = VRT_READY;
        chan->writer_tid = -1;
    }

    return val;
}




int vrt_system(const char *command) {
    if (!command || !command[0]) return 0;

    pid_t pid = fork();
    if (pid < 0) return -1;

    if (pid == 0) {
        
        char *args[4];
        args[0] = "/bin/cfish"; 
        args[1] = "-c";          
        args[2] = (char *)command;
        args[3] = NULL;

        execve(args[0], args, NULL);
        exit(127); 
    }

    
    int status = 0;
    waitpid(pid, &status, 0);
    return WEXITSTATUS(status);
}
