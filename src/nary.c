#include "../include/nary.h"
#include "../include/main.h"
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

#define MAX_PATH_SIZE 100
#define MAX_FILEDIR_NAME_SIZE 20
#define MAX_BLOCKS 20
#define BLOCK_SIZE 1024

#define TRUE 1
#define FALSE 0

void printtree(t_node **root) {
	
	if (*root == NULL) {
	printf("empty narray tree\n");
	}
	else {
	t_node *cnode,*temp;
	cnode=*root;
	while(cnode->left_child!=NULL) {

	//printf("hello\n");
		if(cnode->is_deleted==0)
		printf(" %s%s\n",cnode->data->slocation_full_path,cnode->data->sfile_name);
   cnode=cnode->left_child;
   if(cnode->is_deleted==0)
   printf(" %s%s\n",cnode->data->slocation_full_path,cnode->data->sfile_name);
  // printf("gj\n");
   temp=cnode;
  while(temp->right_siblings!=NULL)
{
    temp=temp->right_siblings;
    if(temp->is_deleted==0)
    printf("%s%s\n",temp->data->slocation_full_path,temp->data->sfile_name);

}

   cnode=cnode->left_child;
}
 if(cnode->is_deleted==0)
 printf("%s%s",cnode->data->slocation_full_path,cnode->data->sfile_name);
 
}
}


t_node *mem_alloc()
{
	t_node * new_node;
	new_node = (t_node *)malloc(sizeof(t_node));
	return new_node;
}

int insert_node(t_node** root, struct File_Descriptor* data)
{
	int n, i,j,count = 1,c;
	char **tokens;
	char path[MAX_PATH_SIZE];
	int counter = 0;
	int flag = 1;

	t_node * previous, *current;

	if(*root == NULL && (strcmp(data->sfile_name,"/") != 0) )
		return 1;

	t_node *new_node;
	new_node = mem_alloc();
	
	//Insertion of the first node
	if(*root == NULL)
	{
		new_node->is_deleted = 0;
		new_node->left_child = NULL;
		new_node->right_siblings = NULL;
		new_node->parent = NULL;
		new_node->data = data;

		//Root now points to newly inserted first node "/"
		*root = new_node;
		return 0;
	}

	new_node->is_deleted = 0;
	new_node->left_child = NULL;
	new_node->right_siblings = NULL;
	new_node->parent = NULL;
	new_node->data = data;
	
	//Tokenizing
	strcpy(path,data->slocation_full_path);
	n = strlen(path);

	if(n==1)
		count = 1;
	else
	{
	for(i=1;i<n;i++){
		if(path[i]=='/')
			count++;
	}
		count++;
	}

	(tokens) = (char **)malloc(sizeof(char*)*count);

	i = 0;
	for(c=0;c<count;c++)
	{
		j = 0;
		tokens[c] = (char *)malloc(sizeof(char) * 50);
		while(path[i] != '/' && path[i]!='\0')
		{
			tokens[c][j] = path[i];
			i++;
			j++;
		}
		i++;
		tokens[c][j] = '\0';
	}

	tokens[0][0] = '/';
	tokens[0][1] = '\0';
	

	
	
	//Traverse the tree and check for the path
	i = 0;
	current = *root;

	while(current != NULL)
	{
		if(current->is_deleted == 0 && strcmp(current->data->sfile_name,tokens[i]) == 0)
		{
			i++;
			if(i == count)
				break;
			current = current->left_child;
			
		}
		//Goto right siblings
		else if(current->right_siblings != NULL)
		{
			current = current->right_siblings;
		}
		else
		{
			flag =0;
			break;
		}
	}
     
	//Invalid positions
	if(flag == 0 || current == NULL)
	{
		return 1;
	}
	
	//Insertion of the new_node
	if(current->left_child == NULL)
	{       new_node->parent=current;
		current->left_child=new_node;
		return 0;
	}
	
	current = current->left_child;
	//previous = current;
	while(current->right_siblings != NULL)
	{
		current = current->right_siblings;
		if (strcmp(current->data->sfile_name,new_node->data->sfile_name)==0)
			return -1;
	}
        new_node->parent=current->parent;
	current->right_siblings = new_node;
	return 0;
}

int delete(t_node *temp){
	
       if(temp==NULL)
           return 0;
       else
        {  
			temp->is_deleted=1;
         delete(temp->left_child);
        while(temp->right_siblings!=NULL)
          {
              temp=temp->right_siblings;
              delete(temp);
          }
}
}

int deletenode(t_node **root, struct File_Descriptor* data){
 int i,n,count=0,c,flag=1;
 char path[100],**tokens;
 t_node *current,*temp;
 temp=NULL;

// go to the location of the file or directory ,ie traverse
strcpy(path,data->slocation_full_path);
printf("the path is %s\n",path);
	n = strlen(path);

	if(n==1)
		count = 1;
	else
	{
	for(i=1;i<n;i++){
		if(path[i]=='/')
			count++;
	}
		count++;
	}

	(tokens) = (char **)malloc(sizeof(char*)*count);

	i = 0;
	for(c=0;c<count;c++)
	{
	int	j = 0;
		tokens[c] = (char *)malloc(sizeof(char) * 50);
		while(path[i] != '/' && path[i]!='\0')
		{
			tokens[c][j] = path[i];
			i++;
			j++;
		}
		i++;
		tokens[c][j] = '\0';
	}

	tokens[0][0] = '/';
	tokens[0][1] = '\0';
	

	
	for(c =0; c<count; c++)
		printf("%s\n",tokens[c]);


	//Traverse the tree and check for the path
	i = 0;
	current = *root;

	while(current != NULL)
	{
		if(current->is_deleted == 0 && strcmp(current->data->sfile_name,tokens[i]) == 0)
		{
			i++;
			if(i == count)
				break;
			current = current->left_child;
			
		}
		//Goto right siblings
		else if(current->right_siblings != NULL)
		{
			current = current->right_siblings;
		}
		else
		{
			flag =0;
			break;
		}
	}
	printf("%s\n",current->data->sfile_name);
    printf("%s\n",current->data->slocation_full_path);
	if(flag == 0 || current == NULL)
	{
		return 1;
	}
    
	//current->is_deleted = TRUE;
	current->is_deleted = 1;
	current = current->left_child;
	int result = delete(current);
	return result;
     
return 0;
}

int deletenodes(t_node **root,char *fullpath)
{
t_node * current;
	int flag =1;
	int result;

	if (*root == NULL)
		return 1;

	int n, i,j,count = 1,c;
	char **tokens;

	n = strlen(fullpath);

	if(n==1)
		count = 1;
	else
	{
		for(i=1;i<n;i++){
			if(fullpath[i]=='/')
				count++;
		}
		count++;
	}
	
	tokens= (char **)malloc(sizeof(char*)*count);

	i = 0;
	for(c=0;c<count;c++)
	{
		j = 0;
		tokens[c] = (char *)malloc(sizeof(char) * 50);
		while(fullpath[i] != '/' && fullpath[i]!='\0')
		{
			tokens[c][j] = fullpath[i];
			i++;
			j++;
		}
		i++;
		tokens[c][j] = '\0';
	}

	tokens[0][0] = '/';
	tokens[0][1] = '\0';

	i = 0;
	current = *root;

	while(current != NULL)
	{
		if(current->is_deleted == 0 && strcmp(current->data->sfile_name,tokens[i]) == 0)
		{
			i++;
			if(i == count)
				break;
			current = current->left_child;
		}
		//Goto right siblings
		else if(current->right_siblings != NULL)
		{
			current = current->right_siblings;
		}
		else
		{
			flag =0;
			break;
		}
	}

	//Invalid positions
	if(flag == 0 || current == NULL)
	{
		return 1;
	}

	//current->is_deleted = TRUE;
	current->is_deleted = 1;
	current = current->left_child;
	result = delete(current);
	return result;

}




/*int main()
{
int k;


//INSERTIONS

t_node *root = NULL;
fd* dir1 = (fd*)malloc(sizeof(fd));
dir1->file_type='d';

dir1->lfile_size=10;
strcpy(dir1->sfile_name,"/");
strcpy(dir1->slocation_full_path,"/");
dir1->llocation_block_no=12;
k=insert_node(&root,dir1);
printf("%d\n",k);


dir1 = (fd*)malloc(sizeof(fd));
dir1->file_type='d';

dir1->lfile_size=10;
strcpy(dir1->sfile_name,"home");
strcpy(dir1->slocation_full_path,"/");
dir1->llocation_block_no=10;
k=insert_node(&root,dir1);
printf("%d\n",k);

dir1 = (fd*)malloc(sizeof(fd));
dir1->file_type='d';

dir1->lfile_size=10;
strcpy(dir1->sfile_name,"another");
strcpy(dir1->slocation_full_path,"/");
dir1->llocation_block_no=15;
k=insert_node(&root,dir1);
printf("%d\n",k);

dir1 = (fd*)malloc(sizeof(fd));
dir1->file_type='d';

dir1->lfile_size=10;
strcpy(dir1->sfile_name,"as");
strcpy(dir1->slocation_full_path,"/");
dir1->llocation_block_no=17;
k=insert_node(&root,dir1);
printf("%d\n",k);

dir1 = (fd*)malloc(sizeof(fd));
dir1->file_type='d';

dir1->lfile_size=10;
strcpy(dir1->sfile_name,"dd");
strcpy(dir1->slocation_full_path,"/");
dir1->llocation_block_no=8;
k=insert_node(&root,dir1);
printf("%d\n",k);

dir1 = (fd*)malloc(sizeof(fd));
dir1->file_type='d';

dir1->lfile_size=10;
strcpy(dir1->sfile_name,"cp");
strcpy(dir1->slocation_full_path,"/home");
dir1->llocation_block_no=1;
k=insert_node(&root,dir1);
printf("%d\n",k);
fd *dir2;
dir2=dir1;
dir1 = (fd*)malloc(sizeof(fd));
dir1->file_type='d';

dir1->lfile_size=10;
strcpy(dir1->sfile_name,"del1");
strcpy(dir1->slocation_full_path,"/home/cp");
dir1->llocation_block_no=19;
k=insert_node(&root,dir1);
printf("%d\n",k);

dir1 = (fd*)malloc(sizeof(fd));
dir1->file_type='f';

dir1->lfile_size=10;
strcpy(dir1->sfile_name,"/aaa");
strcpy(dir1->slocation_full_path,"/home/cp/del1");
dir1->llocation_block_no=4;
k=insert_node(&root,dir1);
printf("%d\n",k);

printf("the nodes in the tree are \n");
printtree(&root);
//k=searchtree(&root,"/home/cp/del1/aaa");
//printf("%d\n 0 if file found 1 if file not found",k);
// after deletion of a directory
printf("\n");
//deletion
int j=deletenodes(&root,"/home");
printtree(&root);

return 0;
}
*/
