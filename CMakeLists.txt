cmake_minimum_required(VERSION 3.26)
project(aos_code C)

set(CMAKE_C_STANDARD 11)

add_executable(aos_code
        basics/01-fork/fork.c
        basics/02-exec/exec.c
        ipc/03-signal/receiver-mask.c
        ipc/03-signal/receiver-timewait.c
        ipc/03-signal/receiver.c
        ipc/03-signal/sender.c
        ipc/04-message_queues/es04.c
        ipc/04-pipes/pipe.c
        ipc/05-fifo/reader.c
        ipc/05-fifo/writer.c
        ipc/es01-signals/main.c
        ipc/es02-pipe/es02.c
        ipc/es03-fifo/es03.c)
