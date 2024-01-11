#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void father(int *p1, int *p2);
void child(int *p1, int *p2);

int main(){

    int p1[2], p2[2];
    pid_t childPid;

    pipe(p1);
    pipe(p2);
    if((childPid = fork())){
        //father
        father(p1, p2);
    } else{
        //child
        child(p1, p2);
    }

    waitpid(childPid,NULL,0);
    return(0);
}

void father(int *p1, int *p2){
    
    char sig = 'R';
    char rSig;
    
    close(p1[0]);
    close(p2[1]);

    while(1){
    printf("I'm the father (PID=%d)\n",getpid());
    sleep(1);
    write(p1[1],&sig,1);
    read(p2[0],&rSig,1);

    }
}

void child(int *p1, int *p2){
    
    char sig = 'R'; 
    char rSig;

    close(p1[1]);
    close(p2[0]);

    while(1){
    read(p1[0],&rSig,1);
    printf("I'm the child (PID=%d)\n",getpid());
    sleep(1);
    write(p2[1],&sig,1);
    }
}
