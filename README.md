# Password Cracker

This program is a simple password cracker that uses brute-force techniques to discover a secret 12-character password. It demonstrates the use of process creation and control in a Linux environment, showcasing the fork(), getpid(), getppid(), and wait() system calls.

## Purpose

The main goals of this project are:

1. To learn about process creation and control in a Linux environment
2. To gain experience with fork(), getpid(), getppid(), and wait() system calls
3. To practice C programming from an operating system perspective
4. To demonstrate how parallel processing can speed up computationally intensive tasks

## Features

- Brute-force password cracking for a 12-character password
- Option to use multiple processes (forking) for faster execution
- Displays process IDs for parent and child processes
- Compares execution time between single-process and multi-process approaches

## Requirements

- Linux environment (tested on Gaul server)
- GCC compiler
- `checkPassword.h` and `checkPassword.o` files (provided separately)

## Compilation

To compile the program, use the following command:

```
gcc -o assignment-1 assignment-1.c checkPassword.o
```

## Usage

Run the program without forking:
```
time ./assignment-1
```

Run the program with forking (using 4 child processes):
```
time ./assignment-1 -f
```

## Output

The program will display the process IDs and the discovered password segments. The output will look similar to this:

```
Process 668954 with parent 666832 cracking the password...
Process 668956 with parent 668954 finds 3-5: def
Process 668955 with parent 668954 finds 0-2: abc
Process 668957 with parent 668954 finds 6-8: 123
Process 668958 with parent 668954 finds 9-11: 456
```

The `time` command will provide execution time information, allowing you to compare the performance of the single-process and multi-process versions.

## Technical Details

- The password is exactly 12 characters long
- Valid characters are in the ASCII range 33-126
- The program uses the `checkPassword()` function to verify password segments
- When forking is enabled, the program creates 4 child processes, each responsible for a 3-character segment of the password

## Limitations

- The program assumes the availability of the `checkPassword()` function
- It's designed for educational purposes and may not be suitable for real-world password cracking scenarios
- The performance improvement from forking may vary depending on the system and the specific password
