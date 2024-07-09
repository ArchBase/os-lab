#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>

int request[10] = {0, 199, 98, 183, 37, 122, 14, 124, 65, 67}, total_head_movement=0, head_position=53, no_of_requests=10, direction=1, max_head = 199;

int get_next_request_index(){
    int i, next_index;

    // initialize init index


    if(direction){
        for(i=0; i<no_of_requests; i++){
            if(request[i] > request[next_index] && request[i] <= head_position && request[i] != -1){
                next_index = i;
            }
        }
        if(request[next_index] == 0){
            direction = 0;
        }
    }
    else{
        for(i=0; i<no_of_requests; i++){
            if(request[i] < request[next_index] && request[i] >= head_position && request[i] != -1){
                next_index = i;
            }
        }
        if(request[next_index] == max_head){
            direction = 1;
        }
    }
    return next_index;
}

int update_direction(int used_index){
    if(direction){
        request[used_index] = max_head+1;
        if(request[used_index] == 0){
            direction = 0;
        }
    }
    else{
        request[used_index] = -1;
        if(request[used_index] == max_head){
            direction = 1;
        }
    }
}

void main(){
    int i, next_index;
    printf("Head movment: \n%d", head_position);
    for(i=0; i< no_of_requests; i++){
        next_index = get_next_request_index();
        printf("-->%d", request[next_index]);
        total_head_movement += abs(head_position-request[next_index]);
        head_position = request[next_index];
        update_direction(next_index);
    }
    printf("\nTotal head movement: %d", total_head_movement);
}


