/*
                                          Program.No:10
                                      FCFS DISK SCHEDULING
                                      ====================
*/
#include<stdio.h>
void main()
{
   int n,head,i,d[20],init,sum=0,tm[20];
   printf("Enter the number of locations:");
   scanf("%d",&n);
   printf("Enter the initial position:");
   scanf("%d",&head);
   init=head;
   printf("Enter the request queue:");
   for(i=0;i<n;i++)
   {
      scanf("%d",&d[i]);
      tm[i]=head-d[i];
      if(tm[i]<0)
      { 
         tm[i]=d[i]-head;
      }
      head=d[i];
      sum=sum+tm[i];
   }
   printf("HEAD MOVEMENT\n=============\n");
   printf("%d",init);
   for(i=0;i<n;i++)
   {
     printf("-->%d",d[i]);
   }
   printf("\nTotal head movement=%d",sum);
}
/*
OUTPUT
======
Enter the number of locations:8
Enter the initial position:53
Enter the request queue:98 183 37 122 14 124 65 67
HEAD MOVEMENT
=============
53-->98-->183-->37-->122-->14-->124-->65-->67
Total head movement=640
*/
