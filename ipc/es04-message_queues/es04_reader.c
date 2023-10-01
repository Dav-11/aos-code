#include <stdio.h>
#include <mqueue.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define OUTPUT_FILE "output.log"
#define QUEUE_NAME "/es04"
#define MSG_SIZE 100

// prio lvl
#define HIGH 1
#define MEDIUM 2
#define LOW 3

void log_message(char *msg, unsigned int priority) {

    // open file
    FILE *file = fopen(OUTPUT_FILE, "a");

    // Check if the file was opened successfully
    if (file == NULL) {

        printf("Error opening the file.\n");
        exit(1);
    }

    time_t raw_time;
    time(&raw_time); // Get current time

    struct tm *time_info;
    time_info = localtime(&raw_time); // Convert to local time

    // Format and print the time as "HH:MM:SS"
    char buffer[10];
    strftime(buffer, sizeof(buffer), "%2H:%2M:%2S", time_info);
    printf("Current time: %s\n", buffer);

    int res = 0;

    switch (priority) {
        case HIGH:

            res = fprintf(file, "[%s] %s %s\n", buffer, "[HIGH]", msg);
            break;
        case MEDIUM:

            res = fprintf(file, "[%s] %s %s\n", buffer, "[MEDIUM]", msg);
            break;
        default:

            res = fprintf(file, "[%s] %s %s\n", buffer, "[LOW]", msg);
    }

    if (res <= 0) {
        printf("error while writing to file");
        exit(1);
    }

    fclose(file);
}


int main() {
    
    // open queue
    mqd_t mqd = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0664, NULL);
    if (mqd < 0) {
        printf("error while opening queue, code:%d", mqd);
        return 1;
    }

    // read attr
    struct mq_attr attr;
    mq_getattr(mqd, &attr);

    char buf[MSG_SIZE];
    unsigned int priority;
    memset(buf, 0, sizeof(buf));

    while (attr.mq_curmsgs != 0) {

        ssize_t size = mq_receive(mqd, buf, MSG_SIZE, &priority);
        if (size < 0) {

            printf("error while receiving message");
            return 1;
        }

        log_message(buf, priority);
    }
}