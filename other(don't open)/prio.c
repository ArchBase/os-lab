#include<stdio.h>
struct priority
{
    int pid;
    int at;
    int bt;
    int prior;
    int ct;
    int tat;
    int wt;
}; 
void main()
{
    int i,j,n;
    int current_time=0;
    float tat=0,wt=0;
    struct priority p[5],temp;
    printf("enter the no of process\n");
    scanf("%d",&n);
    //struct priority p[n],temp;
    printf("enter the arrival time of each process\n");
    for(i=0;i<n;i++)
    {
        p[i].pid=i+1;
        printf("process  %d\n",p[i].pid);
        scanf("%d",&p[i].at);
    }
    printf("enter the burst time of each process\n");
    for(i=0;i<n;i++)
    {
       // p[i].pid=i+1;
        printf("process  %d\n",p[i].pid);
        scanf("%d",&p[i].bt);
    }
    printf("enter the priority of each process\n");
    for(i=0;i<n;i++)
    {
       // p[i].pid=i+1;
        printf("process  %d\n",p[i].pid);
        scanf("%d",&p[i].prior);
    }
    // sort by prior
    for(i=0; i<n-1; i++){
        for(j=0; j<n-i-1; j++){
            if(p[j].prior > p[j+1].prior){
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
    printf("\nSorted: ");
    for(i=0; i<n; i++){printf("\nid: %d at: %d", p[i].pid, p[i].at);}
    /*
    for(i=0;i<n-1;i++)
    {
        for(j=0;j<n-i-1;j++)
        {
            if(p[j].prior>p[j+1].prior)
            {
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }*/
    // calc ct
    
    for(j=0; j<n; j++){
        for(i=0;i<n;i++)
        {
            printf("\nctt: %d, checking p%d, at:%d", p[i].pid, p[i].at, current_time);
            if(p[i].at<=current_time && p[i].pid != -1)
            {
                printf("\nexecuting p%d at: %d bt:%d prior:%d", p[i].pid, p[i].at, p[i].bt, p[i].prior);
                p[i].ct=current_time+p[i].bt;
                current_time=p[i].ct;
                p[i].pid = -1;
            }
            else{
                current_time++;
            }
        }
    }
    // calc tat wt
    for(i=0;i<n;i++)
    {
        p[i].tat=p[i].ct-p[i].at;
        tat=tat+p[i].tat;
        p[i].wt=p[i].tat-p[i].bt;
        wt=wt+p[i].wt;
    }
    tat=tat/(float)n;
    wt=wt/(float)n;
    printf("\naverg tat===%f\n",tat);
    printf("avg wt==%f",wt);
}