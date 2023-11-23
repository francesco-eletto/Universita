#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#define MAXLEN 1024

int fileDuplicator(char *fOutName, char *fInName);    

int main(int argc, char **argv){
    
    char fInName[MAXLEN], fOutName[MAXLEN];

    strcpy(fInName, argv[1]);
    strcpy(fOutName, argv[2]);

    return fileDuplicator(fOutName,fInName);
}

int fileDuplicator(char *fOutName, char *fInName){
    
    int fIn, fOut, count;
    char tmpChar;
    
    if((fIn = open(fInName, O_RDONLY)) == -1) return 1;
    if((fOut = open(fOutName, O_WRONLY | O_CREAT)) == -1) return 2;
    
    while((count = read(fIn, &tmpChar, 1))){
        printf("%c",tmpChar);
        write(fOut, &tmpChar,count);
    }

    close(fIn);
    close(fOut);

    return 0;

}
