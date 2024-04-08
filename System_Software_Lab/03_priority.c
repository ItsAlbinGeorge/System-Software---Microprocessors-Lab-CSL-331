/*
                                          Program.No:3
                                       PRIORITY SCHEDULING
                                       ===================
*/
#include<stdio.h>
#include<stdlib.h>
struct arriv
{
   int pid;
   int btime;
   int priority;
   int wtime;
   int tatime;
}p[10],temp;
void main()
{
   int i,j,n,ttat=0,twt=0;
   float avtat,avwt;
   printf("Enter the number of processes:");
   scanf("%d",&n);
   for(i=0;i<n;i++)
   {
      p[i].pid=i;
      printf("Enter the burst time of P[%d]: ",p[i].pid);
      scanf("%d",&p[i].btime);
      printf("Enter the priority of P[%d]: ",p[i].pid);
      scanf("%d",&p[i].priority);
   }
   for(i=0;i<n;i++)
   {
      for(j=0;j<n-i-1;j++)
      {
         if(p[j].priority<p[j+1].priority)
         {
            temp=p[j];
            p[j]=p[j+1];
            p[j+1]=temp;
         }
      }
   }
   p[0].wtime=0;
   for(i=1;i<n;i++)
   {
     p[i].wtime=0;
     for(j=0;j<i;j++)
     {
        p[i].wtime+=p[j].btime;
     }
   }
   printf("PROCESS\t\tBURST TIME\tPRIORITY\tWAITING TIME\tTURNAROUND TIME\n");
   for(i=0;i<n;i++)
   {
     p[i].tatime=p[i].wtime+p[i].btime;
     ttat+=p[i].tatime;
     twt+=p[i].wtime;
     printf("P[%d]\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].pid,p[i].btime,p[i].priority,p[i].wtime,p[i].tatime);
   }
   avtat=(float)ttat/n;
   avwt=(float)twt/n;
   printf("Average waiting time=%f\n",avwt);
   printf("Average turnaround time=%f\n",avtat);
}
/*
OUTPUT
======
Enter the number of processes:5
Enter the burst time of P[0]: 4
Enter the priority of P[0]: 1
Enter the burst time of P[1]: 9
Enter the priority of P[1]: 8
Enter the burst time of P[2]: 6
Enter the priority of P[2]: 7
Enter the burst time of P[3]: 4
Enter the priority of P[3]: 9
Enter the burst time of P[4]: 3
Enter the priority of P[4]: 2
PROCESS		BURST TIME	PRIORITY	WAITING TIME	TURNAROUND TIME
P[3]		4		9		0		4
P[1]		9		8		4		13
P[2]		6		7		13		19
P[4]		3		2		19		22
P[0]		4		1		22		26
Average waiting time=11.600000
Average turnaround time=16.799999
*/
