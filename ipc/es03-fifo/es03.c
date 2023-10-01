#include<string.h>
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<math.h>

#define BASE_FILE "/tmp/myfifo."
#define MAX_TRY 100
#define BUFFER_SIZE 50 // could be dynamic if malloc is used

int open_fifo_queue() {

    // create string for filename
    int char_num = sizeof(BASE_FILE)/sizeof(char) + 1; // for null terminator
    char file_name[char_num];
    memset(file_name, '\0', char_num);
    strcpy(file_name, BASE_FILE);

    // init queue file descriptor
    int fd = 0;

    for (int try = 0; try < MAX_TRY; try++) {

        memset(file_name, '\0', char_num);
        
        // i
        char str[2];
        sprintf(str, "%d", try);

        // create file name
        strcat(file_name, BASE_FILE);
        strcat(file_name, str);

        fd = open(file_name, O_RDONLY);
        if (fd > 0) {

            // success!
            printf("Opened queue: %s\n", file_name);
            return fd;
        }

        // log error
        printf("Cannot open fifo: %s, error: %d\n", file_name, fd);
    }

    // if no try was successful -> panic
    exit(1);
}

int main() {

    // get queue file descriptor
    int fd = open_fifo_queue();

    // char buffer
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, sizeof(buffer));
    
    // read data
    int ok = read(fd, &buffer, sizeof(buffer));
    if (ok == 0) {
        
        printf("Read Error\n");
        return 1;
    }

    close(fd);

    printf("pre_swap: %s", buffer);

    int real_length = strlen(buffer);
    int length = real_length -1; // remove null terminator
    int mid = floor(length/2);

    for (int i = 0; i < mid; i++) {

        char hold = buffer[length-(i+1)];
        buffer[length-(i+1)] = buffer[i];
        buffer[i] = hold;
    }

    printf("result: %s", buffer);

    return(0);
}
