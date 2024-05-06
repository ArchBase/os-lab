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
}ready_queue[10]={
    {.id = 1, .arrival_time = 0, .burst_time = 3},
    {.id = 2, .arrival_time = 2, .burst_time = 2},
    {.id = 3, .arrival_time = 4, .burst_time = 4},
    {.id = 4, .arrival_time = 5, .burst_time = 5},
    {.id = 5, .arrival_time = 6, .burst_time = 2},
    {.id = 6, .arrival_time = 8, .burst_time = 1}
};

int current_time = 0;
int num_of_processes = 6;
float avg_wait_time = 0, avg_tat = 0;
struct process current_process;
void shift_left(){
    int i;
    for(i=0; i<num_of_processes-1; i++){
        //printf("hai");
        ready_queue[i] = ready_queue[i+1];
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


int run_next_frame(){
    if(ready_queue[0].arrival_time <= current_time){
        current_process = ready_queue[0];
        shift_left();
        execute_process();
        calculate_average();
        return 1;
    }
    else{
        current_time += 1;
        return 0;
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


