#include "uthread.h"
#include "user.h"
void thread_function(){
    int i;
    int uid=get_uthread_id();
    for(i=0;i<5;i++){
        printf(1, "Thread %d is running\n", uid);
        uthread_yield();
    }
    uthread_exit();
}

int main(int argc, char *argv[]){
    uthread_create(thread_function);
    uthread_create(thread_function);
    uthread_create(thread_function);

    
    printf(1, "Main thread is running\n");
    uthread_yield();//it will never return, because we set it to RUNNING and not RUNNABLE   

    exit();
    return 0;
}