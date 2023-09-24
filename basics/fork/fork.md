# Fork
The `fork()` function spawns a new process from the current one, memory will be copy-on-write (will be just a pointer to the first process memory until either one edits it)

## See Processes
```shell
ps -eo user,pid,ppid,cmd | grep './fork'
```
