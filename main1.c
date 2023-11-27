#include <unistd.h> // for write
#include <string.h> // for strlen
#include "fonctions.h"

//First question : Display a welcome message, followed by a simple prompt
int main() {
    char welcomeMsg[] = "Welcome to ENSEA Tiny Shell.\nType 'exit' to quit.\nenseash % "; //message to display
    write(STDOUT_FILENO, welcomeMsg, strlen(welcomeMsg)); //displaying messaging without using printf
    
    return 0;
}