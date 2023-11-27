//This is the code for the second question : Execution of the entered command and return to the prompt 
#include <unistd.h> // for write
#include <string.h> // for strlen
#include <stdlib.h> //for exit
#include "fonctions.h"
#include <sys/wait.h> //for wait 

int main() {
    char welcomeMsg[] = "Welcome to ENSEA Tiny Shell.\nType 'exit' to quit.\nenseash % "; //message to display
    char buf[MAX_COMMAND_LENGTH]
    ssize_t command_size;

    write(1,welcomeMsg,strlen(welcomeMsg));

    while(1){
        write(1,"%",strlen("%"));
        command_size=read(0,buf,MAX_COMMAND_LENGTH);
        execute_command(buf, command_size);
    }
    return 0;
}

void execute_command(char *buf, ssize_t, command_size){
    int pid,status;
    buf[command_size - 1]='\0';
    pid=fork();

    if (pid!=0){//The father waits for the child to execute
        //write(1,"father",strlen("father"));
        wait(status);
    }
    else{
        execlp(buf,buf,(char*)NULL);
        exit(EXIT_SUCCESS);
    }
}
