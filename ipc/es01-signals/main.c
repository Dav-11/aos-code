#include<stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>

#define MAX 100
#define MIN 0
#define WAIT 1

int sum = 0;

void sigusr_handler(int sig_num) {

    printf("%d", sum);
    exit(0);
}

void setHandlers() {

    // sigusr handler
    struct sigaction sigusr_sigaction;
    memset(&sigusr_sigaction, 0, sizeof(struct sigaction));
    sigusr_sigaction.sa_handler = &sigusr_handler;

    // sigterm handler
    struct sigaction sigterm_sigaction;
    memset(&sigterm_sigaction, 0, sizeof(struct sigaction));
    sigterm_sigaction.sa_handler = SIG_IGN; // ignore signal


    sigaction(SIGUSR1, &sigusr_sigaction, NULL);
    sigaction(SIGTERM, &sigterm_sigaction, NULL);
}


int main() {

    setHandlers();

    for (int i = MIN; i <= MAX; i++) {
        
        printf("%d\n", i);
        
        sum += i;

        sleep(WAIT);
    }
}

