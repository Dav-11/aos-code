# Exercise 5 – Shared Memory
Write two programs sharing a memory segment:
- The first one runs in background and waits the memory segment to be filled with the following data:
    ```C
    struct person {
        char name[100];
        char surname[100];
        unsigned int year_of_birth;
    };
    ```
- Once received, each data is printed with the following format:
    ```
    FEDERICO ROSSI 1990
    ```
- The second program reads the three information from standard input and writes them to the shared memory