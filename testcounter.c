#include "types.h"
#include "user.h"

int main(void) {
    int pid;

    pid = fork();
    if (pid < 0) {
        printf(1, "fork error\n");
        exit();
    }

    if (pid == 0) { // 子进程
        ucounter_set(5);
        printf(1, "Child: set counter to 5\n");
        exit();
    } else { // 父进程
        wait();
        printf(1, "Parent: the value of counter is %d\n", ucounter_get());
    }

    exit();
}
