//uthread.h
#include "types.h"
#define STACK_SIZE 256
#define MAX_THREADS 10
#define RUNNING 0
#define RUNNABLE 1
#define UNUSED 2
struct context{
    uint edi;
    uint esi;
    uint ebx;
    uint ebp;
    uint eip;
};

struct uthread{
    char stack[STACK_SIZE];
    struct context *context;
    int state;
    int uid;
};
extern void uthread_create(void (*func)(void));
extern void uthread_exit(void);
extern int get_uthread_id(void);
extern void uthread_yield(void);

