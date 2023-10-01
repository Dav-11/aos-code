# Exercise 1 - Signals
Write a program that:
- Prints all the numbers from 0 to 100 with an interval of 1 second
- Prints, at the end of the execution, the total sum
- Terminates (printing the sum) if it receives `SIGUSR1`
- Does nothing (continuing the counting), if it receives the signal `SIGTERM`