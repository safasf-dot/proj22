#include "uthread.h"
#include "user.h"
#include "types.h"

extern void uthread_switch(struct context **old, struct context *new);
struct uthread uthread_table[MAX_THREADS];

int global_thread_id=1;//reserve 0 for the main thread
struct uthread *current_thread=0;

static int first_call_to_create=1;

void init_thread_context(struct uthread *t, void (*func)(void)){
    // Initialize a thread's context, as if it was just scheduled

    // set up the value of t->context, t->context->eip
    char *stack_top=t->stack+STACK_SIZE;
    stack_top-=sizeof(struct context);
    t->context=(struct context *)stack_top;
    t->context->edi=0;
    t->context->esi=0;
    t->context->ebx=0;
    t->context->ebp=(uint)stack_top;

    // Set the instruction pointer to the function to be executed
    //add your code here

    t->context->eip = (uint)func;

}

void uthread_init(){//initialize the thread table, and set the context of the calling thread
//    printf(1,"entering uthread_init\n");
	for(int i=0;i<MAX_THREADS;i++){
		uthread_table[i].state=UNUSED;
	}
    current_thread=&uthread_table[0];

    //the main thread is set to running, and will not be changed to RUNNABLE ever, so it will not be scheduled
    current_thread->state=RUNNING;    
    init_thread_context(current_thread,0);
}

void uthread_create(void (*func)(void)){
	//create a user thread; don't worry, it will not run immediately like a kernel thread
  //  printf(1,"entering uthread create\n");
	
     if(first_call_to_create){
	     uthread_init();
	     first_call_to_create=0;
     }
    //find an unused thread struct
    struct uthread *t=0;
    for(int i=0;i<MAX_THREADS;i++){
        if(uthread_table[i].state==UNUSED){
            t=&uthread_table[i];
            break;
        }
    }
    if(t==0){
        printf(1,"No available thread structure\n");
        return;
    }

   // printf(1,"found a thread structure, initializing\n");

   //your code here, you should
    // Initialize the thread's context, by calling init_thread_context
    // Set the thread's state to RUNNABLE
    // Set the thread's uid to global_thread_id, and increment global_thread_id
    
    init_thread_context(t, func);
    t->state = RUNNABLE;
    t->uid = global_thread_id++;

}

int get_uthread_id(){    
    return current_thread->uid;
}



void uthread_schedule(void){
//    printf(1,"in schedule\n");
    struct uthread *t, *next_thread=0;
    for(t=uthread_table;t<uthread_table+MAX_THREADS;t++){
        if(t->state==RUNNABLE&&t!=current_thread){
            //find a runnable thread other than current
            next_thread=t;
            break;
        }
    }
    if(next_thread==0&&current_thread->state==RUNNABLE){
        //if no other thread is runnable, we can run the current thread
    //    printf(1,"no other thread is running, keep running the current one\n");
        next_thread=current_thread;
    }else if(next_thread==0) {
        //no available thread
        printf(1,"No available thread, exiting the whole process\n");
        exit();
    }
    next_thread->state=RUNNING;
    if(next_thread!=current_thread){
    //we are switching threads
    //your code here
    //you should call uthread_switch to change context,
    //but before that, you need to update variable current_thread to point to the next thread 

    struct uthread *old = current_thread;
    current_thread = next_thread;
    uthread_switch(&old->context, next_thread->context);

    }
}


void uthread_yield(){
    if(current_thread->uid==0){
        //this must be called from the main thread
       // printf(1,"main thread calling yield\n");
        uthread_schedule();    
        return;//will not reach here
    }
    //your code here
    //you should change the state of the current thread to RUNNABLE, and call uthread_schedule

    current_thread->state = RUNNABLE;
    uthread_schedule();
}

void uthread_exit(){
    //your code here, change the state of the current thread structure to UNUSED and call uthread_schedule

    current_thread->state = UNUSED;
    uthread_schedule();
}
