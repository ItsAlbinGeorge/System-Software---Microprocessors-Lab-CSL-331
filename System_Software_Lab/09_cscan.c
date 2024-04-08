/*
                                          Program.No:9
                                      CSCAN DISK SCHEDULING
                                      =====================
*/
#include<stdio.h>
void main()
{
   int n,head,i,d[20],j,temp,sum=0,pos,diskmax;
   printf("Enter the number of locations:");
   scanf("%d",&n);
   printf("Enter the initial position:");
   scanf("%d",&head);
   printf("Enter the maximum size of disk:");
   scanf("%d",&diskmax);
   printf("Enter the request queue:");
   for(i=0;i<n;i++)
   {
      scanf("%d",&d[i]);
   }
   d[n]=head;
   n++;
   for(i=0;i<n-1;i++)
   {
      for(j=0;j<n-i-1;j++)
      {
         if(d[j]>d[j+1])
         {
            temp=d[j];
            d[j]=d[j+1];
            d[j+1]=temp;
         }
      }
   }
   for(i=0;i<n;i++)
   {
      if(d[i]==head)
      {
         pos=i;
         break;
      }
   }
   printf("HEAD MOVEMENT\n=============\n");
   printf("%d",head);
   for(i=pos+1;i<n;i++)
   {
      printf("-->%d",d[i]);
   }
   printf("-->%d-->0",diskmax);
   for(i=0;i<pos;i++)
   {
     printf("-->%d",d[i]);
   }
   sum=diskmax-head;
   sum+=diskmax;
   sum=sum+d[pos-1];
   printf("\nTotal seek operations=%d",sum);
}
/*
OUTPUT
======
Enter the number of locations:8
Enter the initial position:53
Enter the maximum size of disk:199
Enter the request queue:98 183 37 122 14 124 65 67
HEAD MOVEMENT
=============
53-->65-->67-->98-->122-->124-->183-->199-->0-->14-->37
Total seek operations=382
*/
