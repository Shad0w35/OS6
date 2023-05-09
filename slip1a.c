#include<stdio.h>
 main()
 {
   int i,j,p,r,alloc[10][10],need[10][10],max[10][10],available[10];
   printf("\n Enter the how many process you want:");
   scanf("%d",&p);
   printf(" Enter the how many resources you want:");
   scanf("%d",&r);
   printf("\n Enter the allocation matrix:\n");
   for(i=0;i<p;i++)
    {
     
     printf(" P%d\t",i);
      for(j=0;j<r;j++)
       scanf("%d",&alloc[i][j]);
    }
   printf("\n Enter the maximum demand of matrix:\n");
   for(i=0;i<p;i++)
    {
     printf(" P%d\t",i);
      for(j=0;j<r;j++)
       scanf("%d",&max[i][j]);
    }
   printf("\n Enter the available resource matrix: ");
   for(i=0;i<r;i++)
     {
       scanf("%d",&available[i]);
       
     }
   printf("\n The contents of need array is:");
   for(i=0;i<p;i++)
    {
     printf("\n P%d",i);
      for(j=0;j<r;j++)
       {
	 need[i][j]=max[i][j]-alloc[i][j];
	 printf("\t%d",need[i][j]);
       }
    }
printf("\n The contents Allocation Matrix:");
   for(i=0;i<p;i++)
    {
     printf("\n P%d",i);
      for(j=0;j<r;j++)
       {
	 printf("\t%d",alloc[i][j]);
       }
    }
printf("\n The contents Max Matrix is:");
   for(i=0;i<p;i++)
    {
     printf("\n P%d",i);
      for(j=0;j<r;j++)
       {
	 printf("\t%d",max[i][j]);
       }
    }
printf("\n The contents Available Matrix is:");
   for(i=0;i<r;i++)
     {
             
	 printf("\t%d",available[i]);
       }
    
}