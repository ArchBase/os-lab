#include<stdio.h> 

struct fcfs 
{ 
    int at;   // Arrival time
    int tat;  // Turnaround time
    int ct;   // Completion time
    int bt;   // Burst time
    int wt;   // Waiting time
    int pid;  // Process ID
};

void main() 
{ 
    int n,i,j; 
    float tot_tat=0,tot_wt=0,avg_tat=0,avg_wt=0; 
    printf("Enter the number of processes: "); 
    scanf("%d",&n); 
    struct fcfs p[n], temp; 
    printf("Enter the arrival and burst time for each of the processes\n"); 
    for(i=0;i<n;i++) 
    { 
        p[i].pid=i+1; 
        printf("Process %d: ",p[i].pid); 
        scanf("%d%d",&p[i].at,&p[i].bt); 
    } 

    // Sorting processes based on burst time
    for(i=0;i<n-1;i++) {
        for(j=0;j<n-1-i;j++) {
            if(p[j].bt>p[j+1].bt) {
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }

    // Calculating completion time 
    int current_time=0;
    for(i=0;i<n;i++) 
    {
        int idx=-1,s_bt=9999;
        for(j=0;j<n;j++)
        {
            if(p[j].at<=current_time && p[j].bt!=0 && p[j].bt<s_bt) 
            {
                s_bt=p[j].bt;
                idx=j;
            }
        }
        if(idx==-1)
        {
            current_time++;
            continue;
        }
        p[idx].ct=current_time+p[idx].bt;
        p[idx].tat=p[idx].ct-p[idx].at;
        p[idx].wt=p[idx].tat-p[idx].bt;
       p[idx].bt=0;
        current_time=p[idx].ct;
    }
    printf("proc\tat\tbt\ttat\twt\n");
    // Calculating turn around time and waiting time 
    for(i=0;i<n;i++) { 
        tot_tat+=p[i].tat; 
        tot_wt+=p[i].wt; 
        printf("%d\t%d\t%d\t%d\t%d\n",p[i].pid,p[i].at,p[i].bt,p[i].tat,p[i].wt);
    } 

    printf("Average Turn Around Time: %f\n",tot_tat/n); 
    printf("Average Waiting Time: %f\n",tot_wt/n); 
}