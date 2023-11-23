#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void pidPrint(char *name);
int P457();
int P68();

int main(int argc, char **argv){
    
    pid_t pid;

    pidPrint("P1");

    if((pid = fork())){
        pidPrint("P2");
        P457();
        waitpid(pid, NULL, 0); 
        pidPrint("P9");
        exit(0);
    } else{
        pidPrint("P3");
        P68();
        exit(0);
    }
    return 0;
}

int P68(){

    pid_t pid;

    if((pid = fork())){
        waitpid(pid, NULL, 0);
        pidPrint("P8");
    }else{
        pidPrint("P6");
        exit(0);
    }
    return 0;
}

int P457(){

    pid_t pid;

    if((pid = fork())){
        pidPrint("P4");
        waitpid(pid, NULL, 0);
        pidPrint("P7");
    }else{
        pidPrint("P5");
        exit(0);
    }
    return 0;
}

void pidPrint(char *name){
    printf("%s, pid: %d\n", name, getpid());
    return;
}

