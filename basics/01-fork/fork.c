#include <unistd.h>
#include <stdio.h>

int main() {

    printf("Starting with PID %d!\n", getpid());

    int ret = fork();
    printf("Both prints this message\n");

    if (ret == 0) {

        // Child
        printf("I'm the child and my parent is %d!\n", getppid());
        sleep(20);
    } else {

        // Parent
        printf("I'm the parent and the child has pid %d!\n", ret);
        sleep(20);
    }

    return 0;
}