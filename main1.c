#include <unistd.h> // for write
#include <string.h> // for strlen

//First question : Display a welcome message, followed by a simple prompt
int main1() {
    char welcomeMsg[] = "Welcome to ENSEA Tiny Shell.\nType 'exit' to quit.\nenseash % "; //message to display
    write(STDOUT_FILENO, welcomeMsg, strlen(welcomeMsg)); //displaying messaging without using printf

    return 0;
}