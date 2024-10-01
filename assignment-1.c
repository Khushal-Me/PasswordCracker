/*
Khushal Mehta kmehta73@uwo.ca
Assignment 1 for CS3305
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "checkPassword.h"

// Function to crack the password by trying all combinations in the given range
void crack_password_range(int start, int end) {
    char guess[4] = {0};  // Initialize a guess string with 3 characters and a null terminator

    // Nested loops to generate all combinations of characters from ASCII 33 to 126
    for (guess[0] = 33; guess[0] <= 126; guess[0]++) {
        for (guess[1] = 33; guess[1] <= 126; guess[1]++) {
            for (guess[2] = 33; guess[2] <= 126; guess[2]++) {

                // Call the checkPassword function with the guess and range start as arguments
                if (checkPassword(guess, start) == 0) {  // If password is cracked (returns 0)
                    printf("Process %d with parent %d finds %d-%d: %s\n", 
                           getpid(), getppid(), start, end, guess);  // Print success message
                    return;  // Exit the loop after finding the correct password
                }
            }
        }
    }
}

// Function to fork processes and divide the work among child processes
void fork_and_crack() {
    for (int i = 0; i < 4; i++) {  // Create 4 child processes
        pid_t pid = fork();  // Fork a child process

        if (pid == 0) {  // In the child process
            crack_password_range(i * 3, i * 3 + 2);  // Child cracks a specific range
            exit(0);  // Exit the child process after completing its work
        } else if (pid < 0) {  // If fork fails
            perror("Fork failed");  // Print error message
            exit(1);  // Exit with failure code
        }
    }

    // Parent process waits for all child processes to complete
    for (int i = 0; i < 4; i++) {
        wait(NULL);  // Wait for one child process to finish
    }
}

int main(int argc, char *argv[]) {
    int use_fork = 0;  // Flag to determine whether to use forking

    // Check if the user passed the "-f" flag to enable forking
    if (argc > 1 && strcmp(argv[1], "-f") == 0) {
        use_fork = 1;  // Set the flag to use forking
    }

    // Print a message indicating the start of the cracking process
    printf("Process %d with parent %d cracking the password...\n", getpid(), getppid());

    if (use_fork) {
        fork_and_crack();  // Use forking to parallelize the cracking process
    } else {
        // Without forking, sequentially crack the password in 4 different ranges
        for (int i = 0; i < 4; i++) {
            crack_password_range(i * 3, i * 3 + 2);  // Try cracking in specific range
        }
    }

    return 0;  // Program exits successfully
}
