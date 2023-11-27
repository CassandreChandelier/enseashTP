//This is the code for the second question : Execution of the entered command and return to the prompt 
#include <unistd.h> // for write
#include <string.h> // for strlen
#include <stdlib.h> //for exit
#include <unistd.h> // for read, fork, and for constants like STDOUT_FILENO and STDIN_FILENO.
#include <sys/wait.h> //for wait function

#define MAX_COMMAND_LENGTH 100 //Sets the maximum length of the command that can be entered by the user. 

int main() {
    char command[MAX_COMMAND_LENGTH];// to store the entered command
    char prompt[] = "enseash % ";//the prompt displayed to the user

    while (1) {
        write(STDOUT_FILENO, prompt, strlen(prompt)); // Print the prompt

       // Reading the command entered by the user
        ssize_t bytesRead = read(STDIN_FILENO, command, MAX_COMMAND_LENGTH);//Reads the command entered by the user in the input and stores it in the command array.
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

