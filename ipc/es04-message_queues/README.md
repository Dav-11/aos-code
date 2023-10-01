# Exercise 4 – Message Queues
Write a logger based on message queues that:
- Receives messages and print them into a text file
- Each message has a priority (HIGH, MEDIUM, LOW)
- Higher priority messages have always the precedence
- Example of output file:
    ```
    14:12:01 [HIGH] Dangerous event occurred
    14:12:51 [LOW] This is not very important
    ```
- Write a second program that sends random messages to test it