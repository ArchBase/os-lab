// NOT WORKING

#include <stdio.h>

struct Frame{
    int id, used, time_added;
};

int ref_string[25]={1, 2, 3, 4, 2, 1, 5, 6, 2, 1, 2, 3, 7, 6, 3, 2, 1, 2, 3, 6}, ref_string_length=20, no_pf_frames=4, ref_string_index=0, total_hit=0, total_fault=0;

struct Frame frames[4];
int frame_index=0;

int current_time=0;

int get_next_page(){
    ref_string_index++;
    return ref_string[ref_string_index-1];
}
int is_page_inside(int page_id){
    int i;
    for(i=0; i<no_pf_frames; i++){
        if(frames[i].id == page_id){
            return 1;
        }
    }
    return 0;
}

void replace_page(int id){
    struct Frame *next_replace_page;
    int i;
    next_replace_page = &frames[0];
    for(i=0; i<no_pf_frames; i++){
        if(frames[i].time_added < next_replace_page->time_added){
            next_replace_page = &frames[i];
        }
    }
    next_replace_page->id = id;
}

void add_page(int id){
    if(frame_index <= no_pf_frames-1){
        frames[frame_index].id = id;
        frames[frame_index].time_added = current_time;
        frame_index++;
    }
    else{
        replace_page(id);
    }
}

void main(){
    int i, next_page;
    for(i=0; i<ref_string_length; i++){
        current_time += 1;
        next_page = get_next_page();
        if(is_page_inside(next_page)){
            total_hit += 1;
        }
        else{
            add_page(next_page);
            total_fault += 1;
        }
    }
    printf("Total page fault: %d", total_fault);
    printf("Total page hit  : %d", total_hit);
}

