#include <stdio.h>
#include <stdlib.h>

int request[10] = {98, 183, 37, 122, 14, 124, 65, 67, 0, 199}, total_head_movement=0, head_position=53, no_of_requests=10, direction=1;
int invalid[10];

void sort_ascending(){
    void swap(int *a, int *b){
        int temp;
        temp = *a;
        *a = *b;
        *b = temp;
    }
    int i, j;
    for(i=0; i<no_of_requests-1; i++){
        for(j=0; j<no_of_requests-i-1; j++){
            if(request[j] > request[j+1]){
                swap(&request[j], &request[j+1]);
            }
        }
    }
}
void sort_left(){
}

void main(){
    int i;
    sort_ascending();
    for(i=0; i<no_of_requests; i++){
        printf(" %d", request[i]);
    }
    printf("Head movment: \n%d", head_position);
    for(i=0; i< no_of_requests; i++){
        printf("-->%d", request[i]);
        total_head_movement += abs(head_position-request[i]);
        head_position = request[i];
    }
    printf("\nTotal head movement: %d", total_head_movement);
}


