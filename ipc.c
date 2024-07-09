#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

void main(){
    int i, shmid;
    char buff[100];
    void *sm;
    shmid = shmget((key_t)2345, 1024, 0666|IPC_CREAT);
    printf("Key: %d", shmid);
    sm = shmat(shmid, NULL, 0);
    printf("Attached at: %p", sm);
    printf("enter data: ");
    read(0, buff, 100);
    strcpy(sm, buff);
    printf("You wrote: %s\n", (char *)sm);
}