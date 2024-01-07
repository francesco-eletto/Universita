#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    
    pid_t pid;
    while(1){
        if((pid = fork())){
            wait(NULL);
            printf("Father Woke-up\n");
            sleep(1);
        }else{
            printf("Child Woke-up\n");
            sleep(1);
            exit(0);
        }
    }

    return(0);
}
