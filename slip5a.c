#include<stdio.h>

 main()
 {
   int i,j,m,n,p,r,no,k=0,flag=0,flag1=0,flag2=0,request[10],safe[10],alloc[10][10],need[10],max[10][10],finish[10],work[10],available[10];

   printf("\n Enter the how many process you want:");
   scanf("%d",&p);
   printf(" Enter the how many resources you want:");
   scanf("%d",&r);
   printf("\n Enter the allocation matrix:\n");
   for(i=0;i<p;i++)
    {
     finish[i]=-1;
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
       work[i]=available[i];
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
 loop:for(i=0;i<p;i++)
    {
     if(finish[i]==-1)
      { 
	j=m=0;
	while(j<r)
	 {
	  if(need[i][j]<=work[j])
	     j++;
	  else
	    {
	      printf("\n P%d has to wait, it is not safe",i);
	      m=-1;
	      break;
	    }
	 }
       if(m!=-1)
	 {
	   for(n=0;n<r;n++)
	     work[n]=work[n]+alloc[i][n];
	   finish[i]=0;
	   printf("\n P%d is safe",i);
	   safe[k]=i;
	   k++;
	   printf("\n Safe sequence is: ");
	   for(n=0;n<k;n++)
	     printf("  P%d",safe[n]);
	 }
      }
    }
   for(n=0;n<p;n++)
    {
     if(finish[n]==-1)
       goto loop;
     else
     if(flag==1)
       goto end;
    }
   flag=1;
   k=0;
   printf("\n Enter the procees number which give new request: ");
   scanf("%d",&no);
   printf(" Enter the new request from the process P%d: ",no);
   for(j=0;j<r;j++)
    scanf("%d",&request[j]);
   for(i=0;i<r;i++)
    {
      if(request[i] <= need[no][i])
	 flag1=0;
      else
       {
	 flag1=1;
	 break;
       }
     if(request[i]<=available[i])
       flag2=0;
     else
       {
	 flag2=1;
	 break;
       }
   }
  if(flag1==0 && flag2==0)
   {
    if(no<p)
     {
       for(j=0;j<r;j++)
	{
	  available[j]=available[j]-request[j];
	  work[j]=available[j];
	  alloc[no][j]=alloc[no][j]+request[j];
	  need[no][j]=need[no][j]-request[j];
	}
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
   for(i=0;i<p;i++)
     finish[i]=-1;
  end:for(i=0;i<p;i++)
    {
     if(finish[i]==-1)
       goto loop;
     else
     if(i==p-1)
      {
	  printf("\n Yes, System is in safe state. \n Request can be granted immediately. ");
	  break;
      }
    }
  }
 else
  printf("\n So P%d has to wait since resource are not available. \n Request can not be granted immediately. ",no);
// getch();
 return 0;
 }