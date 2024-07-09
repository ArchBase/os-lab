#include <stdio.h>

struct Block{
    int id, free, size;
};
struct Process{
    int id, size, allocated;
};

struct Block blocks[10] = {
    {.id=1, .free=1, .size=100},
    {.id=2, .free=1, .size=500},
    {.id=3, .free=1, .size=200},
    {.id=4, .free=1, .size=300},
    {.id=5, .free=1, .size=600}
};
struct Process processes[10] = {
    {.id=1, .size=212},
    {.id=2, .size=417},
    {.id=3, .size=112},
    {.id=4, .size=299}
};
int no_of_blocks=5, no_of_processes=4;

void sort_blocks(){
    struct Block temp;
    int i, j;
    for(i=0; i<no_of_blocks-1; i++){
        for(j=0; j<no_of_blocks-i-1; j++){
            if(blocks[j].size < blocks[j+1].size){
                temp = blocks[j];
                blocks[j] = blocks[j+1];
                blocks[j+1] = temp;
            }
        }
    }
}

int allocate_process(struct Process current_process){
    sort_blocks();
    int i;
    for(i=0; i<no_of_blocks; i++){
        if(blocks[i].size >= current_process.size && blocks[i].free){
            printf("Process: P%d of size: %d allocated in block: %d of size: %d remaining: %d\n", current_process.id, current_process.size, blocks[i].id, blocks[i].size, blocks[i].size - current_process.size);
            blocks[i].free = 0;
            blocks[no_of_blocks].id = blocks[no_of_blocks-1].id + 1;
            blocks[no_of_blocks].free = 1;
            blocks[no_of_blocks].size = blocks[i].size - current_process.size;
            no_of_blocks += 1;
            return 1;
        }
    }
    printf("Process: P%d of size: %d must wait\n", current_process.id, current_process.size);
    return 1;
}

void main(){
    int i;
    sort_blocks();
    for(i=0; i<no_of_processes; i+=allocate_process(processes[i]));
}

