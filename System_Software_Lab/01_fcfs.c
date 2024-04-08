/*
                                          Program.No:1
                               FIRST COME FIRST SERVE SCHEDULING
                               =================================
*/
#include<stdio.h>
#include<stdlib.h>
struct arriv
{
   int pid;
   int btime;
   int atime;
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
      printf("Enter the arrival time of P[%d]: ",p[i].pid);
      scanf("%d",&p[i].atime);
   }
   for(i=0;i<n;i++)
   {
      for(j=0;j<n-i-1;j++)
      {
         if(p[j].atime>p[j+1].atime)
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
     p[i].wtime-=p[i].atime;
   }
   printf("PROCESS\t\tBURST TIME\tARRIVAL TIME\tWAITING TIME\tTURNAROUND TIME\n");
   for(i=0;i<n;i++)
   {
     p[i].tatime=p[i].wtime+p[i].btime;
     ttat+=p[i].tatime;
     twt+=p[i].wtime;
     printf("P[%d]\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].pid,p[i].btime,p[i].atime,p[i].wtime,p[i].tatime);
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
Enter the arrival time of P[0]: 1
Enter the burst time of P[1]: 8
Enter the arrival time of P[1]: 0
Enter the burst time of P[2]: 3
Enter the arrival time of P[2]: 5
Enter the burst time of P[3]: 2
Enter the arrival time of P[3]: 7
Enter the burst time of P[4]: 9
Enter the arrival time of P[4]: 4
PROCESS		BURST TIME	ARRIVAL TIME	WAITING TIME	TURNAROUND TIME
P[1]		8		0		0		8
P[0]		4		1		7		11
P[4]		9		4		8		17
P[2]		3		5		16		19
P[3]		2		7		17		19
Average waiting time=9.600000
Average turnaround time=14.800000
*/
