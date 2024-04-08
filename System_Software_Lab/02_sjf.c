/*
                                            Program.No:2
                                   SHORTEST JOB FIRST SCHEDULING
                                   =============================
*/
#include<stdio.h>
#include<stdlib.h>
struct arriv
{
   int pid;
   int btime;
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
   }
   for(i=0;i<n;i++)
   {
      for(j=0;j<n-i-1;j++)
      {
         if(p[j].btime>p[j+1].btime)
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
   printf("PROCESS\t\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
   for(i=0;i<n;i++)
   {
     p[i].tatime=p[i].wtime+p[i].btime;
     ttat+=p[i].tatime;
     twt+=p[i].wtime;
     printf("P[%d]\t\t%d\t\t%d\t\t%d\n",p[i].pid,p[i].btime,p[i].wtime,p[i].tatime);
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
Enter the burst time of P[0]: 2
Enter the burst time of P[1]: 7
Enter the burst time of P[2]: 4
Enter the burst time of P[3]: 1
Enter the burst time of P[4]: 5
PROCESS		BURST TIME	WAITING TIME	TURNAROUND TIME
P[3]		1		0		1
P[0]		2		1		3
P[2]		4		3		7
P[4]		5		7		12
P[1]		7		12		19
Average waiting time=4.600000
Average turnaround time=8.400000
*/
