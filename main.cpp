//
// Created by cassa on 27/11/2023.
#include <unistd.h> // for write
#include <string.h> // for strlen

int main() {
    char welcomeMsg[] = "Welcome to ENSEA Tiny Shell.\nType 'exit' to quit.\nenseash % ";
    write(STDOUT_FILENO, welcomeMsg, strlen(welcomeMsg));

    return 0;
}
//
