# Signals
Signals are a type of IPC (**I**nter **P**rocess **C**ommunication)
> Signals can be sent by processes or by the OS

## Characteristics
- Unidirectional
- No data transfer
- The only information content is the signal type
- Asynchronous

## Examples
- Elapsed timer
- I/O operation success or failure
- Exceptions
- User defined events

## Common POSIX Signals
| POSIX signals | Number | Default action     | Description                                    |
|---------------|--------|--------------------|------------------------------------------------|
| SIGHUP        | 1      | Terminate          | Controlling terminal disconnected              |
| SIGINT        | 2      | Terminate          | Terminal interrupt                             |
| SIGILL        | 4      | Terminate and dump | Attempt to execute illegal instruction         |
| SIGABRT       | 6      | Terminate          | Process abort signal                           |
| SIGKILL       | 9      | Terminate          | Kill the process                               |
| SIGSEGV       | 11     | Terminate and dump | Invalid memory reference                       |
| SIGSYS        | 12     | Terminate and dump | Invalid system call                            |
| SIGPIPE       | 13     | Terminate          | Write on a pipe with no one to read it         |
| SIGTERM       | 15     | Terminate          | Process terminated                             |
| SIGUSR        | 116    | Terminate          | User-defined signal 1                          |
| SIGUSR        | 217    | Terminate          | User-defined signal 2                          |
| SIGCHLD       | 18     | Ignore             | Child process terminated, stopped or continued |
| SIGSTOP       | 23     | Suspend            | Process stopped                                |

## `kill()` function
The kill function sends a signal

```C
#include <signal.h>
#include <sys/types.h>
int kill(pid_t pid, int sig);
```
- `pid` -> PID of the receiver process
- `sig` -> signal to send (a SIG_* constant)
- Returns `0` on success, `-1` on error

## `sigaction()` function
The sigaction function is used to override the default behaviour after receiving a message

```C
#include <signal.h>
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
```
- `signum` -> signal to catch (a SIG_* constant)
- `act` -> new settings to apply to register a handler function
- `oldact` -> output variable, it saves the old settings if not NULL
- Returns `0` on success, `-1` on error

### ES
```C
struct sigaction {
    void        (*sa_handler)(int);
    void        (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t    sa_mask;
    int         sa_flags;
    void        (*sa_restorer)(void);
};
```
- `sa_handler`: Handler function (or SIG_IGN)
- `sa_sigaction`: Allows you to specify an handler that accept an input data. Flags must contain `SA_SIGINFO`.
- `sa_mask`: set a mask to block certain signals
- `sa_flags`: various options
- `sa_restorer`: not intended to be used by user applications, not in POSIX, do not use