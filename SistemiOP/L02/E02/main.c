#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv){

    int n, t, i = 0;

    n = atoi(argv[1]);
    t = atoi(argv[2]);
    
    printf("processo: %d, pid: %d, ppid: %d\n", i, getpid(), getppid());

    for(i = 0; i < n; i++){
        if(fork()){
            if(fork()){
                exit(0);
            }
            printf("processo: %d, pid: %d, ppid: %d\n", i, getpid(), getppid());
        }else{
            printf("processo: %d, pid: %d, ppid: %d\n", i, getpid(), getppid());
        }
    }
    printf("processo foglia: %d, pid: %d, ppid: %d, sleeps for %d seconds\n", i, getpid(), getppid(), t);
    sleep(t);
    return 0;
}
