#include "types.h"
#include "user.h"

#define DEBUG 0

extern int clone(void *(*fn)(void *),void *stack,void *arg);
extern void join(int tid,void **ret_p,void **stack);
extern void thread_exit(void *ret);


int xthread_create(int * tid, void * (* start_routine)(void *), void * arg)
{
    // example implementation
    
    void * stack=malloc(4096);
   if(DEBUG) printf(1,"obtain stack addr %x and calling clone with input stack parameter %x\n",stack,stack+4096);
    
    int pid=clone(start_routine,stack+4096,arg);

    if(pid<0)
	    return -1;
    else{
	    *tid=pid;
	    return 1;
    }
}


void xthread_exit(void * ret_val_p)
{
    // example implementation
  thread_exit(ret_val_p);
    
}


void xthread_join(int tid, void ** retval)
{
    // example implementation 
    //
    int stack;
 if(DEBUG)  printf(1,"calling join with tid=%d retval=%x stack addr %x\n",tid,retval,&stack);
    join(tid,retval,(void **)&stack);
    free(((void*)stack)-4096);
}
