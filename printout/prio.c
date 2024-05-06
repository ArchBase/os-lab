#include <stdio.h>
struct process{
    int arrival_time, burst_time, priority, complete_time, start_time, id;
    float wait_time, tat;
}process_queue[10]={
    {.id = 1, .arrival_time = 0, .burst_time = 3, .priority = 2},
    {.id = 2, .arrival_time = 2, .burst_time = 5, .priority = 6},
    {.id = 3, .arrival_time = 1, .burst_time = 4, .priority = 3},
    {.id = 4, .arrival_time = 4, .burst_time = 2, .priority = 5},
    {.id = 5, .arrival_time = 6, .burst_time = 9, .priority = 7},
    {.id = 6, .arrival_time = 5, .burst_time = 4, .priority = 4},
    {.id = 7, .arrival_time = 7, .burst_time = 10, .priority = 10}
};
int current_time = 0, num_of_processes = 7, ready_queue_index = 0;
float avg_wait_time = 0, avg_tat = 0;
struct process current_process, ready_queue[10];
void sort_ready_queue_on_priority(){
    int i, j;
    struct process temp;
    for(i=0; i<ready_queue_index-1; i++){
        for(j=0; j<ready_queue_index-i-1; j++){
            if(ready_queue[j].priority > ready_queue[j+1].priority){
                temp = ready_queue[j];
                ready_queue[j] = ready_queue[j+1];
                ready_queue[j+1] = temp;
            }
        }
    }
}
void update_ready_queue(){
    int i;
    for(i=0; i<num_of_processes; i++){
        if(process_queue[i].id != -1 && process_queue[i].arrival_time <= current_time){
            ready_queue[ready_queue_index] = process_queue[i];
            ready_queue_index += 1;
            process_queue[i].id = -1;
        }
    }
    sort_ready_queue_on_priority();
}
void shift_left(){
    int i;
    for(i=0; i<ready_queue_index-1; i++){
        ready_queue[i] = ready_queue[i+1];
    }
    ready_queue_index -= 1;
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
    update_ready_queue();
    if(ready_queue_index > 0){
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