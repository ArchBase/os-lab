#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

int is_vowel(char c){
    char vowels[5]={'a', 'e', 'i', 'o', 'u'};
    int i;
    for(i=0; i<5; i++){
        if(c == vowels[i]){
            return 1;
        }
    }
    return 0;
}

void main(){
    int i, shmid, len, count_vowel, count_white, count_consonent;
    void *sm;
    char buff[100];
    shmid = shmget((key_t)2345, 1024, 0666);
    sm = shmat(shmid, NULL, 0);
    strcpy(buff, sm);
    printf("\nData in memory: %s", buff);
    len = strlen(buff);
    for(i=0; i<len; i++){
        if(is_vowel(buff[i])){
            count_vowel++;
        }
        if(buff[i] == ' '){
            count_white++;
        }
    }
    count_consonent = len - (count_vowel + count_white);
    printf("\nThere are: ");
    printf("\t%d vowels", count_vowel);
    printf("\t%d white spaces", count_white);
    printf("\t%d consonents", count_consonent);
}