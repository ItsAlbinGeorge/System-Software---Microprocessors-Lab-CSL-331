/*
                                          Program.No:4
                                     ROUND ROBIN SCHEDULING
                                     ======================
*/
#include<stdio.h>
#include<stdlib.h>
struct process
{
  int pid;
  int btime;
  int rtime;
}p[10];
void round_robin(int num,int quantum)
{
   int i,time=0,remaining_processes=num,current_time_slice=0;
   while(remaining_processes>0)
   {
      for(i=0;i<num;i++)
      {
         if(p[i].rtime==0)
            continue;
         if(p[i].rtime<=quantum)
         {
            time+=p[i].rtime;
            current_time_slice=p[i].rtime;
            p[i].rtime=0;
         }
         else
         {
            time+=quantum;
            p[i].rtime-=quantum;
            current_time_slice=quantum;
         }
         printf("Process P[%d] executed %d time units from %d to %d\n",p[i].pid,current_time_slice,time-current_time_slice,time);
         if(p[i].rtime==0)
            remaining_processes--;
      }
   }
}
void main()
{
  int i,n,quantum;
  printf("Enter the number of process:");
  scanf("%d",&n);
  printf("Enter the time quantum:");
  scanf("%d",&quantum);
  for(i=0;i<n;i++)
  {
    p[i].pid=i;
    printf("Enter the burst time of P[%d]:",p[i].pid);
    scanf("%d",&p[i].btime);
    p[i].rtime=p[i].btime;
  }
  round_robin(n,quantum);
}
/*
OUTPUT
======
Enter the number of process:5
Enter the time quantum:3
Enter the burst time of P[0]:5
Enter the burst time of P[1]:2
Enter the burst time of P[2]:3
Enter the burst time of P[3]:1
Enter the burst time of P[4]:7
Process P[0] executed 3 time units from 0 to 3
Process P[1] executed 2 time units from 3 to 5
Process P[2] executed 3 time units from 5 to 8
Process P[3] executed 1 time units from 8 to 9
Process P[4] executed 3 time units from 9 to 12
Process P[0] executed 2 time units from 12 to 14
Process P[4] executed 3 time units from 14 to 17
Process P[4] executed 1 time units from 17 to 18
*/
