#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

void main(){
    int shmid;
    void *sm;
    char buff[100];
    shmid = shmget((key_t)2345, 1024, 0666);
    sm = shmat(shmid, NULL, 0);
    printf("\nData in memory: %s", (char*)sm);
}