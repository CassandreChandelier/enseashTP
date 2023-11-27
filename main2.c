#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

int main() {
    char command[MAX_COMMAND_LENGTH];
    char prompt[] = "enseash % ";

    while (1) {
        write(STDOUT_FILENO, prompt, strlen(prompt)); // Print the prompt

        // Read the command entered by the user
        ssize_t bytesRead = read(STDIN_FILENO, command, MAX_COMMAND_LENGTH);
        if (bytesRead <= 0) {
            write(STDOUT_FILENO, "\n", 1); // Print a newline and exit on empty input or error
            break;
        }

        // Check if the command is "exit" to terminate the loop
        command[bytesRead - 1] = '\0'; // Remove newline character from the input
        if (strcmp(command, "exit") == 0) {
            write(STDOUT_FILENO, "Bye bye\n", 8);
            break;
        }

        // Execute the command
        int child_pid = fork();

        if (child_pid < 0) {
            write(STDOUT_FILENO, "Error forking process\n", 22);
            exit(EXIT_FAILURE);
        } else if (child_pid == 0) {
            // Child process
            execlp(command, command, NULL); // Execute the command
            // If execlp returns, an error occurred
            write(STDOUT_FILENO, "Command not found\n", 18);
            exit(EXIT_FAILURE);
        } else {
            // Parent process waits for child to finish
            wait(NULL);
        }
    }

    return 0;
}
