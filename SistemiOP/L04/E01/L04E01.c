#include <stdio.h>

int main{

int val;

fscanf(stdin,"%d",&val);
if(val%2){
    fprintf(stderr,"%d",val);
}else{
    fprintf(stdout,"%d",val);
}
return 0;
}
