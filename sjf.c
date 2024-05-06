#include <stdio.h>

// class Process Manager
struct process{
    int arrival_time;
    int burst_time;
    int complete_time;
    int start_time;
    int id;
    float wait_time;
    float tat;
}process_queue[10]={
    {.id = 1, .arrival_time = 0, .burst_time = 4},
    {.id = 2, .arrival_time = 0, .burst_time = 2},
    {.id = 3, .arrival_time = 3, .burst_time = 1},
    {.id = 4, .arrival_time = 5, .burst_time = 5},
    {.id = 5, .arrival_time = 6, .burst_time = 3},
    {.id = 6, .arrival_time = 8, .burst_time = 1}
};

int current_time = 0;
int num_of_processes = 6;
float avg_wait_time = 0, avg_tat = 0;
struct process current_process;
struct process ready_queue[10];
int ready_queue_index = 0;

void swap(struct process *p1, struct process *p2){
    struct process temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void sort_ready_queue_on_burst_time(){
    int i, j;
    for(i=0; i<num_of_processes-1; i++){
        for(j=0; j<num_of_processes-i-1; j++){
            if(ready_queue[j].burst_time > ready_queue[j+1].burst_time){
                swap(&ready_queue[j], &ready_queue[j+1]);
            }
        }
    }
}

void update_ready_queue(){
    int i;
    
    for(i=0; i<num_of_processes; i++){
        
        if(process_queue[i].id != -1){
            //printf("updatign ready queue%d\n", process_queue[i].id);    
            if(process_queue[i].arrival_time <= current_time){
                ready_queue[ready_queue_index] = process_queue[i];
                ready_queue_index += 1;
                process_queue[i].id = -1;
            }
        }
    }
    sort_ready_queue_on_burst_time();
}

void clear_ready_queue(){
    ready_queue_index = 0;
}

void shift_left(){// change shift array to ready queue
    int i;
    for(i=0; i<num_of_processes-1; i++){
        //printf("hai");
        ready_queue[i] = ready_queue[i+1];
        ready_queue_index--;
    }
}

void execute_process(){
    current_process.start_time = current_time;
    current_time += current_process.burst_time;
    current_process.complete_time = current_time;
    current_process.tat = current_process.complete_time - current_process.arrival_time;
    current_process.wait_time = current_process.tat - current_process.burst_time;

    printf("P%d\t\t%d\t\t%d\t\t%f\t\t%f\n", current_process.id, current_process.start_time, current_process.complete_time, current_process.wait_time, current_process.tat);
}

void calculate_average(){
    avg_wait_time += current_process.wait_time;
    avg_tat += current_process.tat;
}

int is_empty(){
    if(ready_queue_index <= 0){
        return 1;
    }
    else{
        return 0;
    }
}

int run_next_frame(){
    update_ready_queue();
    if(is_empty() == 1){
        current_time += 1;
        return 0;
    }
    else{
        //printf("executing");
        current_process = ready_queue[0];
        clear_ready_queue();
        execute_process();
        calculate_average();
        return 1;
    }
}


void main(){

    printf("Process    Start time    Complete time    Wait time    T.A.T\n");
    int i;
    for(i=0; i<num_of_processes; ){
        i += run_next_frame();
    }
    printf("\n\nAvg W.T: %f\t Avg T.A.T: %f\n\n", avg_wait_time/num_of_processes, avg_tat/num_of_processes);
}


