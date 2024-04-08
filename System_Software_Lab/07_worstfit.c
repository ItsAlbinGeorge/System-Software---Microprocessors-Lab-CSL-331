/*
                                          Program.No:7
                                  WORST FIT MEMORY ALLOCATION
                                  ===========================
*/
#include<stdio.h>
void main()
{
   int i,j,b[10],p[10],fragments[10],np,nb,temp,top=0;
   static int blockarr[10],processor[10];
   printf("Enter the number of blocks:");
   scanf("%d",&nb);
   for(i=1;i<=nb;i++)
   {
      printf("Enter the size of block %d: ",i);
      scanf("%d",&b[i]);
   }
   printf("Enter the number of processes:");
   scanf("%d",&np);
   for(i=1;i<=np;i++)
   {
      printf("Enter the size of process %d: ",i);
      scanf("%d",&p[i]);
   }
   for(i=1;i<=np;i++)
   {
      for(j=1;j<=nb;j++)
      {
         if(blockarr[j]!=1)
         {
            temp=b[j]-p[i];
            if(temp>=0)
            {
               if(top<temp)
               {
               processor[i]=j;
               top=temp;
               }
            }
         }
      }
      fragments[i]=top;
      blockarr[processor[i]]=1;
      top=0;
   }
   printf("\nProcess\tProcess size\tBlock Number\tBlock Size\tFragments\n");
   for(i=1;i<=np;i++)
   {
     printf("  %d\t\t%d\t\t%d\t\t%d\t\t%d\n",i,p[i],processor[i],b[processor[i]],fragments[i]);
   }
}
/*
OUTPUT
======
Enter the number of blocks:5
Enter the size of block 1: 9
Enter the size of block 2: 2
Enter the size of block 3: 8
Enter the size of block 4: 5
Enter the size of block 5: 6
Enter the number of processes:5
Enter the size of process 1: 1
Enter the size of process 2: 7
Enter the size of process 3: 4
Enter the size of process 4: 1
Enter the size of process 5: 1

Process	Process size	Block Number	Block Size	Fragments
  1		1		1		9		8
  2		7		3		8		1
  3		4		5		6		2
  4		1		4		5		4
  5		1		2		2		1
*/
