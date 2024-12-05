#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

void main(){
    int i, shmid, len, j, max_size=100, flag=0;
    void *sm;
    char buff[100], reverse[100];
    shmid = shmget((key_t)2345, 1024, 0666);
    sm = shmat(shmid, NULL, 0);
    strcpy(buff, sm);
    printf("\nData in memory: %s", buff);
    len = strlen(buff);
    
    //check palindrome

    //remove first '\n' from buff
    for(i=0; buff[i]!='\0'; i++){
        if(buff[i] == '\n'){
            buff[i] = '\0';
        }
    }
    
    //create reverse string
    i=0;
    j=len;
    while(buff[i] != '\0'){
        reverse[j] = buff[i];
        j--;
        i++;
    }

    //check equality
    i=0;
    j=len;
    while(buff[i] != '\0'){
        if(buff[i] != reverse[i]){
            flag = 1;
        }
        i++;
    }

    //print result
    if(flag == 1){
        printf("\nis not palindrome");
    }
    else{
        printf("\nis palindrome");
    }
}