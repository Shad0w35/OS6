#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
void allocate(int a[],int n)
{
int i;

for(i=0;i<n;i++)
a[i]=rand()%50;
}

int main(int argc,char *argv[])
{
int rank,size,n,max=0,min=51,count,*a=NULL,i;
rand();
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD,&size);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
n=atoi(argv[1]);
printf("\n Rank=%d n=%d\n",rank,n);
count=n/size;
if(rank==0)
{
a=(int *) malloc(n*sizeof(int));

allocate(a,n);
}

for(i=0;i<count;i++)
{
printf("\t%d\n",a[i]);
if(a[i]>max)
max=a[i];
if(a[i]<min)
min=a[i];
}

printf("\nmax=%d\t min=%d",max,min);

MPI_Finalize();
}
