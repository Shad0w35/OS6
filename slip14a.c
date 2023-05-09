#include <stdio.h>
#include <stdlib.h>
#define SIZE 100

#define NEWNODE (struct direntry *)malloc(sizeof(struct direntry))

struct direntry
{
char fname[14];
int start,count;
struct direntry *next;
}
*dirst=NULL,*dirend=NULL;

int bitvector[SIZE];

void main()
{
int ch1=0,i,j,k,n,flag;
char fname[14];
struct direntry *t1,*t2;
for(i=0;i<SIZE;i++)
{ bitvector[i]=rand()%2;
}

while(1)
{
  printf("\n\n1. Print Bit Vector");
  printf("\n2. Create File");
  printf("\n3. Print Directory");
  printf("\n4. Delete File");
  printf("\n5. Exit");
  printf("\nEnter Your Choice : ");
  scanf("%d",&ch1);
  switch(ch1)
  {
    case 1 :
      for(i=0;i<SIZE;i++)
	printf("%4d",bitvector[i]);
      break;
    case 2 :
      if(dirst==NULL)
	dirst=dirend=NEWNODE;
      else
      {
	dirend->next=NEWNODE;
	dirend=dirend->next;
      }
      dirend->next=NULL;
      printf("\nEnter A Filename : ");
      scanf("%s",dirend->fname);
      printf("\nEnter The Number of Blocks To Allocate : ");
      scanf("%d",&n);
      dirend->count=n;
      for(i=0;i<100;i++)
      {
       if(bitvector[i]==1) //found free block
       {
	for(j=i;j<i+n;j++) //find next n free blocks
	{
	 if(bitvector[j]!=1)//not free
	  break;
	}//for

	if(j==i+n) //found n contiguous free blocks
	{
	 dirend->start=i;
	 for(k=i;k<j;k++) //allocate block
	  bitvector[k]=0;
	 break;
	}//if
       }//outer if
      }
      break;
  case 3 :
     printf("\nDirectory : ");
     printf("\n--------------------------");
     printf("\nFilename     Start  Count");
     printf("\n--------------------------");
     for(t1=dirst;t1!=NULL;t1=t1->next)
      printf("\n%-10s %5d %5d",t1->fname,t1->start,t1->count);
     printf("\n--------------------------");
     break;
  case 4 :
     printf("\nEnter a Filename : ");
     scanf("%s",fname);
     t1=dirst;
     while(t1!=NULL)
     {
      if(strcmp(t1->fname,fname)==0)
	break;
      t2=t1;
      t1=t1->next;
     }
     if(t1!=NULL)//file found
     {
      for(i=t1->start;i<t1->start+t1->count;i++)
       bitvector[i]=1;  //free blocks

      if(t1==dirst)
	dirst=dirst->next;
      else
	t2->next=t1->next;
      if(dirst==NULL)
	dirend=NULL;

      free(t1);
     }
     else
      printf("\nFile not found..\n");
     break;
    case 5: exit(0);
   }
 }

}