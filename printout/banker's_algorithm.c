#include <stdio.h>
struct process{
    int id;
    int need[3], alloc[3];
}processes[5] = {
    {.id = 0, .need = {0, 0, 0}, .alloc = {0, 1, 0}},
    {.id = 1, .need = {2, 0, 2}, .alloc = {2, 0, 0}},
    {.id = 2, .need = {0, 0, 0}, .alloc = {3, 0, 3}},
    {.id = 3, .need = {1, 0, 0}, .alloc = {2, 1, 1}},
    {.id = 4, .need = {0, 0, 2}, .alloc = {0, 0, 2}}
};
int available[3] = {0, 0, 0}, no_of_processes = 5, num_of_resources = 3;
int can_allocate(struct process p){
    int i;
    for(i=0; i<num_of_resources; i++){
        if(available[i] < p.need[i]){
            return 0;
        }
    }
    return 1;
}
void update_available(struct process p){
    int i;
    for(i=0; i<3; i++){
        available[i] += p.alloc[i];
    }
}
void main(){
    int deadlocked = 0, i, runnable = 0, executed = 0;
    printf("Simulating:\n");
    while(!deadlocked){
        runnable = 0;
        for(i=0; i<no_of_processes; i++){
            if(processes[i].id != -1){
                runnable = can_allocate(processes[i]);
                if(runnable){
                    printf("\texecuting P%d\n", i);
                    update_available(processes[i]);
                    processes[i].id = -1;
                    executed += 1;
                }
            }
        }
        if(runnable == 0 && executed < no_of_processes){
            printf("Deadloack Occured, System is not in safe state\n");
            deadlocked = 1;
        }
        else if(runnable == 0 && executed >= no_of_processes){
            printf("Execution complete, System is in safe state\n");
            deadlocked = 1;
        }
    }
}