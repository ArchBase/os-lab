#include <stdio.h>
#include <stdlib.h>

int request[10] = {98, 183, 37, 122, 14, 124, 65, 67}, total_head_movement=0, head_position=53, no_of_requests=8;

void main(){
    int i;
    printf("Head movment: \n%d", head_position);
    for(i=0; i< no_of_requests; i++){
        printf("-->%d", request[i]);
        total_head_movement += abs(head_position-request[i]);
        head_position = request[i];
    }
    printf("\nTotal head movement: %d", total_head_movement);
}


