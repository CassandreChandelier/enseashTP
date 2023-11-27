#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

void execute_command(char *buf, ssize_t command_size);

int main() {
    // Welcome message and initial prompt
    char welcomeMsg[] = "Welcome to ENSEA Tiny Shell.\nType 'exit' or Ctrl+D to quit.\nenseash % ";
    // Display welcome message
    //write(STDOUT_FILENO, welcomeMsg, strlen(welcomeMsg));
    char buf[MAX_COMMAND_LENGTH];
    ssize_t command_size;

    // Read and execute commands in a loop
    while(1) {
        // Display prompt for user input
        write(STDOUT_FILENO, "enseash % ", strlen("enseash % "));

        // Read the command entered by the user
        command_size = read(STDIN_FILENO, buf, MAX_COMMAND_LENGTH);

        // Check for 'exit' or Ctrl+D to quit
        if (command_size == 0 || (command_size == 5 && strncmp(buf, "exit\n", 5) == 0)) {
            write(STDOUT_FILENO, "Bye\n", strlen("Bye\n"));
            break; // Exit the loop if 'exit' or Ctrl+D is entered
        }

        // Execute the entered command
        execute_command(buf, command_size);
    }
    return 0;
}

// Function to execute the entered command
void execute_command(char *buf, ssize_t command_size) {
    int pid, status;

    // Ensure null termination of the command string
    buf[command_size - 1] = '\0';

    // Create a child process to execute the command
    pid = fork();

    if (pid != 0) {
        // Parent process waits for the child process to finish
        waitpid(pid, &status, 0);
    } else {
        // Child process executes the command
        execlp(buf, buf, (char*)NULL);
        exit(EXIT_SUCCESS);
    }
}

