# Exercise 3 - FIFOs
Write a program that:
- Starts and creates a FIFO with name `/tmp/myfifo.0`. If the FIFO already exists or cannot be created, it tries `/tmp/myfifo.1`, `/tmp/myfifo.2`, etc... until one succeeds
- Once the FIFO is created, the program waits on it and prints any character string coming from the FIFO, in reverse order
- Try the program with an echo bash command:
```bash
echo “Ciao” > /tmp/myfifo
```