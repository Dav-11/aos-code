# Exercise 2 - Pipe
Write a parallel program of 3 processes (by forking) that computes the following sum:
- Σ (1.5)^n for n=1 to n=12
- Each process computes 4 items of the sum, but only the main process prints the total sum
- Use an unnamed pipe as communication mechanisms

## notes
To compile use
```bash
gcc -o es02 es02.c -lm
```
> `-lm` is used to link the `libm.a` library 