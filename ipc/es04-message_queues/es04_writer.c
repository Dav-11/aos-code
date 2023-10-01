#include <stdio.h>
#include <mqueue.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define OUTPUT_FILE "output.log"
#define QUEUE_NAME "/es04"
#define MSG_SIZE 100
#define MSG_NUM 20

// prio lvl
#define HIGH 1
#define MEDIUM 2
#define LOW 3

char messages[4][MSG_SIZE];
unsigned int lvl[3];

int main() {

    strcpy(messages[0], "Message 1");
    strcpy(messages[1], "Message 2");
    strcpy(messages[2], "Message 3");
    strcpy(messages[3], "Message 4");

    lvl[0] = HIGH;
    lvl[1] = MEDIUM;
    lvl[2] = LOW;

    // create attr
    struct mq_attr attr;
    attr.mq_maxmsg = 10;        // maxvalue: cat /proc/sys/fs/mqueue/queues_max
    attr.mq_msgsize = MSG_SIZE; // maxvalue: cat /proc/sys/fs/mqueue/msgsize_max
    attr.mq_flags = 0;
    attr.mq_curmsgs = 0;

    // open queue
    mqd_t mqd = mq_open(QUEUE_NAME, O_CREAT | O_WRONLY, 0664, &attr);
    if (mqd < 0) {
        printf("error while opening queue, code:%d", mqd);
        return 1;
    }

    for (int i = 0; i < MSG_NUM; ++i) {

        int index_priority = i%3;
        int index_message = i%4;

        ssize_t ret = mq_send(mqd, messages[index_message], MSG_SIZE, lvl[index_priority]);
        if (ret < 0) {
            printf("error while sending message, code:%d\n", (int) ret);
            return 1;
        }

        printf("Sent message=\"%s\" w/ priority=%d\n", messages[index_message], lvl[index_priority]);
        sleep(2);
    }

    mq_close(mqd);
    return 0;
}