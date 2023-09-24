# Exec
The `exec*()` family of functions
- They load a new program and replace the current process image with it
- They call the `execve` syscall

## Exec family
```C
#include <unistd.h>
int execl (const char *path, const char *arg, ... );
int execlp(const char *file, const char *arg, ... );
int execle(const char *path, const char *arg, ..., char * const envp[]);
int execv (const char *path, char * const argv[]);
int execvp(const char *file, char * const argv[]);
int execve(const char *path, char * const argv[], char * const envp[]);
```
Exec* letters meaning:
- `-l` functions accept list of parameters `NULL`-terminated
- `-v` functions accept an array of `NULL`-terminated strings
- `-p` functions search the **PATH** environment variable
- `-e` functions allow to specify new environment variables