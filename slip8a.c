#include<stdio.h>
#include<stdlib.h>
#define SIZE 100
#define NEWNODE (struct direntry *)malloc(sizeof(struct direntry))
#define NEWBLK (struct blknode *)malloc(sizeof(struct blknode))

struct blknode
{
	int bno;	
	struct blknode *next;
}*curr,*prev;
struct direntry
{
	char fname[14];
	int start,end;
	struct blknode *blist;
	struct direntry *next;
}*dirst=NULL,*dirend=NULL;
int bitvector[SIZE];
void main()
{
	int ch=0,i,j,n;
	char fname[14];
	struct direntry *t1,*t2;
	//randomize();
	for(i=0;i<SIZE;i++)
	{
		bitvector[i]=rand()%2;
	}
	while(ch!=5)
	{
		printf("\n1.Print Bit Vector");
		printf("\n2.Create File");
		printf("\n3.Print Directpry");
		printf("\n4.Delete File");
		printf("\n5.Exit");
		printf("\nEnter your choice: ");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:	for(i=0;i<SIZE;i++)
					   		printf("%4d",bitvector[i]);
					  	 break;
			case 2:	if(dirst==NULL)
							dirst=dirend=NEWNODE;
						else
						{
							dirend->next=NEWNODE;
							dirend=dirend->next;
						}
						dirend->next=NULL;
						printf("\nEnter a Filename: ");
						scanf("%s",dirend->fname);
						printf("\nEnter the number of blocks to allocate: ");
						scanf("%d",&n);
						dirend->blist=NULL;
						i=0;
						while(n>0)
						{
							if(bitvector[i]==1)
							{
								curr=NEWBLK;
								curr->bno=i;
								curr->next=NULL;
								if(dirend->blist==NULL)
								{
									dirend->start=i;
									dirend->blist=curr;
									prev=curr;
								}
								else
								{
									prev->next=curr;
									prev=curr;
								}
								bitvector[i]=0;
								n--;
								if(n==0)
									break;
							}
							i++;
						}
						dirend->end=i;
						break;
						
						case 3:	printf("\nDirectory");
									printf("\nFilename	 Start	 End");
									for(t1=dirst;t1!=NULL;t1=t1->next)
									{
										printf("\n%-14s \t%5d\t %3d",t1->fname,t1->start,t1->end);
									}
									break;
									
						case 4:	printf("\nEnter a Filename: ");
								scanf("%s",fname);
								t1=dirst;
								while(t1!=NULL)
								{
									if(strcmp(t1->fname,fname)==0)
										break;
									t2=t1;
									t1=t1->next;
								}
								if(t1!=NULL)
								{	
									for(curr=t1->blist;curr!=NULL;)
									{
										bitvector[curr->bno]=1;
										prev=curr;
										curr=curr->next;
										free(prev);
									}	
									if(t1==dirst)
										dirst=NULL;
									free(t1);
								}
								else
									printf("\nFile not found..");
								break;
							
							case 5:	exit(0);
		}
	}
}
