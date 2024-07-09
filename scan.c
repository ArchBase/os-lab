#include <stdio.h>
#include <stdlib.h>

struct Request{
    int visited;
    int position;
};

struct Request new_request(int position){
    struct Request new_request;
    new_request.visited = 0;
    new_request.position = position;
    return new_request;
}

int request[10] = {98, 183, 37, 122, 14, 124, 65, 67, 0, 199}, total_head_movement=0, head_position=53, no_of_requests=10, max_head=199, direction=0;
struct Request request_queue[10];

void init_request_queue(){
    int i;
    for(i=0; i<no_of_requests; i++){
        request_queue[i] = new_request(request[i]);
    }
}

struct Request get_next_request(){
    struct Request next_request;
    int i, index=0;
    if(direction){
        next_request = new_request(0);
        for(i=0; i<no_of_requests; i++){
            if(request_queue[i].position>next_request.position && request_queue[i].position<head_position && request_queue[i].visited!=1){
                next_request = request_queue[i];
                index = i;
            }
        }
        if(next_request.position == 0){
            direction = 0;
        }
        request_queue[index].visited = 1;
        return next_request;
    }
    else{
        next_request = new_request(max_head);
        for(i=0; i<no_of_requests; i++){
            if(request_queue[i].position<next_request.position && request_queue[i].position>head_position && !request_queue[i].visited){
                next_request = request_queue[i];
                index = i;
            }
        }
        if(next_request.position == max_head){
            direction = 1;
        }
        request_queue[index].visited = 1;
        return next_request;
    }
}

void main(){
    int i;
    struct Request next_request;
    init_request_queue();
    printf("Head movment: \n%d", head_position);
    for(i=0; i< no_of_requests; i++){
        next_request = get_next_request();
        printf("-->%d", next_request.position);
        total_head_movement += abs(head_position-next_request.position);
        head_position = next_request.position;
    }
    printf("\nTotal head movement: %d", total_head_movement);
}

