//
// Created by cassa on 27/11/2023.
#include <unistd.h> // for write
#include <string.h> // for strlen

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

int main2() {
    char command[MAX_COMMAND_LENGTH];
    char prompt[] = "enseash % ";

    while (1) {
        write(STDOUT_FILENO, prompt, strlen(prompt)); // Print the prompt

       // Reading the command entered by the user
        ssize_t bytesRead = read(STDIN_FILENO, command, MAX_COMMAND_LENGTH);
        if (bytesRead <= 0) {
            write(STDOUT_FILENO, "\n", 1);  // Printing a newline and exit on empty input or error
            break;
        }

        // Executing the command
        command[bytesRead - 1] = '\0'; // To remove newline character from the input
        int child_pid = fork();

        if (child_pid < 0) {
            write(STDOUT_FILENO, "Error forking process\n", 22);
            exit(EXIT_FAILURE);
        } else if (child_pid == 0) {
            // Child process
            execlp(command, command, NULL);  // Executing the command
           // If execlp returns, a message error is displayed
            write(STDOUT_FILENO, "Command not found\n", 18);
            exit(EXIT_FAILURE);
        } else {
            // Parent process waits for child to finish (td)
            wait(NULL);
        }
    }

    return 0;
}

