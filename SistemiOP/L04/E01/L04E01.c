#include <stdio.h>

int main(){

int val;
do {
fscanf(stdin,"%d",&val);
if(val%2){
    fprintf(stderr,"%d",val);
}else{
    fprintf(stdout,"%d",val);
}
} while(val!=0);
return 0;
}
