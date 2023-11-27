#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

void execute_command(char *buf, ssize_t command_size);

int main() {
    char welcomeMsg[] = "Welcome to ENSEA Tiny Shell.\nType 'exit' to quit.\nenseash % ";
    char buf[MAX_COMMAND_LENGTH];
    ssize_t command_size;

    write(STDOUT_FILENO, welcomeMsg, strlen(welcomeMsg));

    while(1) {
        write(STDOUT_FILENO, "enseash % ", strlen("enseash % "));
        command_size = read(STDIN_FILENO, buf, MAX_COMMAND_LENGTH);
        execute_command(buf, command_size);
    }
    return 0;
}

void execute_command(char *buf, ssize_t command_size) {
    int pid, status;
    buf[command_size - 1] = '\0';
    pid = fork();

    if (pid != 0) {
        waitpid(pid, &status, 0);
    } else {
        execlp(buf, buf, (char*)NULL);
        exit(EXIT_SUCCESS);
    }
}

