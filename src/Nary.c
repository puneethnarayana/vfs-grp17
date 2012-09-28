#include "../include/main.h"
#include "../include/nary.h"
#include<string.h>
#include<stdlib.h>


struct nAryTree *createRoot(struct File_Descriptor *fd) {

	struct nAryTree *nRootPtr;
	struct nAryTree *root;
	nRootPtr= (struct nAryTree *) malloc (sizeof(struct nAryTree));
	//char name[]="ROOT";
	/*strcpy(fd->sfile_name,"ROOT");
	strcpy(fd->slocation_full_path,"ROOT");
	fd->sfile_type='D';
	fd->lfile_size=0;*/
	nRootPtr->fd_tree=fd;
	nRootPtr->leftChild=NULL;
	nRootPtr->rightSibling=NULL;		
	root=nRootPtr;	
	//free(nRootPtr);
	return nRootPtr;

}


struct nAryTree *nTreeChild(struct File_Descriptor *fd,struct nAryTree *root) {
	
	struct nAryTree *currPtr,*rightNode,*leftNode;	
	char cfilepath[100];//specifies the current file path of the node to be placed 
	char delimiter[]="/";
	char *token[50];
	int i,count=0;

	printf("\nIn nary tree creating child\n");
	
	if(root == NULL) {
		printf("Directory not found");
	return NULL;
	}


	printf("\nhi\n");
	printf("\nFile Path Name=%s\n",fd->slocation_full_path);
	strcpy(cfilepath,fd->slocation_full_path);
		for(i=0;cfilepath[i]!='\0';i++){  //Counts the number of '/' in the file path of the received file descriptor
			if(cfilepath[i]=='/')
				{count++;}
		}

	token[0]= strtok(cfilepath,delimiter);
		for(i=1;i<count+1;i++)
			token[i]=strtok(NULL,delimiter);

	currPtr=root;
	i=0;
	printf("\nCount=%d\n",count);
	
	printf("\n%s\n",currPtr->fd_tree=fd->sfile_name);
	
	printf("\nafter malloc\n");
			rightNode=(struct nAryTree *)calloc(1,sizeof(struct nAryTree));
			leftNode=(struct nAryTree *)calloc(1,sizeof(struct nAryTree));
	
	//Logic for traversing through left  child
		while(i<count)			 
		{
							
			printf("\n token[1]=%s \t file Name=%s",token[1],currPtr->fd_tree->sfile_name);
			
			if(strcasecmp(token[1],currPtr->fd_tree->sfile_name)==0)
			{
				printf("\nIn if part of N-AryTree Child creation\n");
				while(currPtr->rightSibling!=NULL)
					currPtr=currPtr->rightSibling;

				/*strcpy(rightNode->fd_tree->sfile_name,fd->sfile_name);
				printf("\nIn n are child\n");
				strcpy(rightNode->fd_tree->slocation_full_path,fd->slocation_full_path);
				rightNode->fd_tree->sfile_type=fd->sfile_type;
				rightNode->fd_tree->lfile_size=fd->lfile_size;*/

				rightNode->fd_tree=fd;
				rightNode->leftChild=NULL;
				rightNode->rightSibling=NULL;
				currPtr->rightSibling=rightNode;
				
				//printf("rightNode not created");	
			}
			else
			{
								printf("\nIn else part of N-AryTree Child creation\n");
				while(currPtr->leftChild!=NULL)
					currPtr=currPtr->leftChild;
				
				printf("\n\n");
				printf("\nIn else part of N-AryTree Child creation\n");
				printf("\nfile name=%s\n",fd->sfile_name);
				printf("\nfile name=%s\n",fd->slocation_full_path);
				printf("\nfile type=%c\n",fd->sfile_type);
				printf("\n%d\n",sizeof(leftNode->fd_tree->sfile_name));	

				//leftNode->fd_tree->sfile_name=fd->sfile_name;
				/*strcpy(leftNode->fd_tree->sfile_name,fd->sfile_name);
				printf("\nfile name=%s\n",leftNode->fd_tree->sfile_name);
				strcpy(leftNode->fd_tree->slocation_full_path,fd->slocation_full_path);
				printf("\nfile name=%s\n",leftNode->fd_tree->sfile_name);
				leftNode->fd_tree->sfile_type=fd->sfile_type;
				printf("\nfile name=%s\n",leftNode->fd_tree->sfile_name);
				leftNode->fd_tree->lfile_size=fd->lfile_size;
				printf("\nfile name=%s\n",leftNode->fd_tree->sfile_name);*/

				leftNode->fd_tree=fd;
				leftNode->leftChild=NULL;
				printf("\nfile name=%s\n",leftNode->fd_tree->sfile_name);
				leftNode->rightSibling=NULL;
				printf("\nfile name=%s\n",leftNode->fd_tree->sfile_name);
				printf("\nfile name=%s\n",leftNode->fd_tree->slocation_full_path);
				printf("\nfile type=%c\n",leftNode->fd_tree->sfile_type);
				//printf("\n%u\n",leftNode);			
				currPtr->leftChild=leftNode;
			}
		i++;
		}



return root;
}


void print(struct nAryTree *root)
{
	//struct nAryTree *currPtr;

	//currPtr=root;
	printf("\n root file name=%s\n",root->fd_tree->sfile_name);
	//printf("\nThe left child created are::");
	if(root->leftChild!=NULL)
	{
		//printf("\n%s",currPtr->fd_tree->sfile_name);
		//printf("\n%s",currPtr->fd_tree->slocation_full_path);
		//printf("\n%c",currPtr->fd_tree->sfile_type);
		//printf("\n%d",currPtr->fd_tree->lfile_size);
			print(root->leftChild);
	
	}

	printf("%s\n",root->fd_tree->sfile_name);
	
	if(root->rightSibling!=NULL)
	{
		//printf("\n%s",currPtr->fd_tree->sfile_name);
		//printf("\n%s",currPtr->fd_tree->slocation_full_path);
		//printf("\n%c",currPtr->fd_tree->sfile_type);
		//printf("\n%d",currPtr->fd_tree->lfile_size);
			print(root->rightSibling);	
	}
	printf("\n");
}
