#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#include "../include/nary.h"
#include "../include/vfs_17.h"

#define TRUE 1
#define FALSE 0

t_node* returnnode(t_node* root, char* path)
{
   	t_node* retnode = NULL;
	t_node* temp = root;
	char new[1024][80];
    char * pch;
	int i=1,t=0,cnt=0;
	
	if(root == NULL)
  	{
   		return NULL;
 	}
	
	pch = strtok (path,"/");
	strcpy(new[0],"/");
    while (pch != NULL)
    {
    strcpy(new[i],pch);
    i++;
    pch = strtok (NULL, "/");

    }
	cnt = i;
	int count = 0,flag=0;
	
	if(strcmp(root->data->sfile_name,new[0])!=0)
	{
		return NULL;
	}

	while(1)
	{
    	if(strcmp(temp->data->sfile_name,new[count])==0)
    	{  
  			retnode = temp; 
        	count++;
        	if(count == cnt)
          	break;
        	if(temp->left!=NULL){
        		temp = temp->left;
			}
			else
			{
				    retnode = NULL;
					break;
			}
      		flag = 0;
      		
      		if(strcmp(temp->data->sfile_name,new[count])==0)
      		{  
          	    retnode = temp;
           		count++;
            	if(count == cnt){
					break;
				}
				if(temp->left == NULL)
 				{ 
 					retnode = NULL;
  					break;
 				}

   				if(temp->left!=NULL)
					temp = temp->left;
      		}
      		else
      		{
				if(temp->sibling == NULL)
                {  
					flag = 0;
                    break;
                }
                
        	   	while(temp->sibling!=NULL)
            	{
					
					temp=temp->sibling;
               		if(strcmp(temp->data->sfile_name,new[count])==0)
                	{  
        	       	   retnode = temp;
            	   	   flag = 1;
              		    break;
               		 }
               		 
      			 }
       			if(flag == 0)
       			 {
              	  	retnode = NULL;
             		break;
       			 }
   		      }
        
			}
	  }
	  return retnode;
      
}

int move_node(t_node* root,char* source_path,char* destination_path)
{
	//printtree(root);	
	//printf("in move node function of nary %s\n",root->data->sfile_name);
	t_node *temp = root;
	
	t_node *node = returnnode(temp,source_path);
	//printf("got node is %s\n",node->data->sfile_name);
	t_node *node2 = returnnode(temp,destination_path);
	//printf("got node2 is %s\n",node2->data->sfile_name);
	if(node == NULL || node2 == NULL)
    {
    	//printf("\nError!!");
    	return -1;
    }

	if(node->is_deleted == TRUE || node2->is_deleted == TRUE)
    {
   		//printf("\nWrong path!!");
    	return -1;
  	}
	
	int i=0;
	//printf("%d",i);
	t_node* new_node = (t_node*)malloc(sizeof(t_node));
	new_node->sibling = NULL;
	if(node->left == NULL){
		//printf("No directory or path in source dir/n");
	}
	else{
		node = node->left;
	}
	new_node->parent = node->parent;
	new_node->is_deleted = node->is_deleted;
	new_node->data = (struct File_Descriptor*)malloc(sizeof(struct File_Descriptor));
  	new_node->data->sfile_type = node->data->sfile_type;
	
	new_node->data->lfile_size = node->data->lfile_size;
	strcpy(new_node->data->sfile_name,node->data->sfile_name);
	strcpy(new_node->data->slocation_full_path,node->data->slocation_full_path);

           new_node->data->llocation_block_no = node->data->llocation_block_no;

	if(node->left!=NULL)
	{
		new_node->left = (t_node*)malloc(sizeof(t_node));
		new_node->left->parent = new_node;
		create_copy(node->left,new_node->left,new_node);
	}
	else
		new_node->left = NULL;

	struct File_Descriptor* data = new_node->data;
	strcpy(data->slocation_full_path,destination_path);
	new_node->parent = node2;
	if(new_node->left!=NULL)
		copy_path(new_node->left);
	if(node2->left == NULL)
  		node2->left = new_node;
	else
  	{
    	 node2 = node2->left;
         while(node2->sibling!=NULL)
       	 	node2 = node2->sibling;
   		node2->sibling = new_node;
 	 }
	 delete_node(&root,source_path);
	 //printf("printing after move_dir/n");
	 //printtree(root);
	 //printf("end of printing after move_dir/n");	
	 return 0;
}


int create_copy(t_node* old_node,t_node* new_node,t_node* par)
{
	if(old_node == NULL)
    	return;
	int i=0;
	strcpy(new_node->node_name,old_node->node_name);
	new_node->is_deleted = old_node->is_deleted;
	new_node->data = (struct File_Descriptor*)malloc(sizeof(struct File_Descriptor));
    new_node->data->sfile_type = old_node->data->sfile_type;
	new_node->left_traversed = old_node->left_traversed;
	new_node->data->lfile_size = old_node->data->lfile_size;
	strcpy(new_node->data->sfile_name,old_node->data->sfile_name);
	strcpy(new_node->data->slocation_full_path,old_node->data->slocation_full_path);
	
    new_node->data->llocation_block_no = old_node->data->llocation_block_no;
	new_node->parent = par;
 	if(old_node->left!=NULL)
  	{
    	new_node->left = (t_node*)malloc(sizeof(t_node));
     	create_copy(old_node->left,new_node->left,new_node);
   	}

 	if(old_node->sibling!=NULL)
  	{
    	new_node->sibling = (t_node*)malloc(sizeof(t_node));
     	create_copy(old_node->sibling,new_node->sibling,par);
   	}
	return 0;
}
 
int copy_path(t_node* node)
{
	if(node == NULL)
    	return;
  	struct File_Descriptor* data = node->data;
  	struct File_Descriptor* data1 = node->parent->data;
 	char* newpath = (char*)malloc(sizeof(data1->slocation_full_path)+sizeof(data1->sfile_name)+2);
    strcpy(newpath,data1->slocation_full_path);
    strcat(newpath,"/");
    strcat(newpath,data1->sfile_name);
    strcat(newpath,"\0");
    strcpy(data->slocation_full_path,newpath);
   	if(node->left!=NULL)
    {
    	copy_path(node->left);
    }
  	if(node->sibling!=NULL)
    	copy_path(node->sibling);
	return 0;
}

int delete_node(t_node** root,char* fullpath)
{

	t_node* temp = *root;	
	t_node* node = returnnode(temp,fullpath);
	if(node == NULL)
    {
   		//printf("\nNo such node!!");
    	return -1;
   	}

	//printf("\nString..%s",node->data->sfile_name);
	int flag = 0;
	node->is_deleted = TRUE;
	if(node->left!=NULL)
  	{ 
  		node = node->left;
 		delete_recursively(node);  
  	}   

    return 0;

}


int delete_recursively(t_node* node)
{
	if(node == NULL)
      return;
    node->is_deleted = TRUE;
  	if(node->left!=NULL)
    	delete_recursively(node->left);
  	if(node->sibling!=NULL)
   		delete_recursively(node->sibling);
  	return 0;
}
    
    void printtree(t_node *root)
    {
    t_node *temp=root;
    //printf("----------Current VFS Structure----------\n\n%s",temp->node_name);
    temp=temp->left;
    //printf("\n%s",temp->node_name);
    while(temp!=root && temp!=NULL)
    {

    if(temp->left!=NULL && temp->left_traversed == 0 )
    {
		//printf("\nLeft of - %s",temp->data->sfile_name);
		temp=temp->left;
		if(temp->is_deleted==0) {}
		//printf("\nLeft - %s",temp->data->sfile_name);
    }
    else 
    {
		if(temp->sibling!=NULL )
		{
		temp->left_traversed = 0;
		//printf("\nsibling of - %s",temp->data->sfile_name);
		temp=temp->sibling;
		if(temp->is_deleted==0) {}
		//printf("\nsibling - %s",temp->data->sfile_name);
		}
		else
		{
		temp->left_traversed = 0;
		temp=temp->parent;
		temp->left_traversed = 1;
		}
	}
    }
    //printf("\n\n");
    }
    

    t_node* insert_node (struct File_Descriptor* fd1,t_node *root)//change return type to int, parameter: FD
    {
    t_node *temp=root;
    int rootcheck = 0;
    int i = 1,pos=0,j=0,y,z;
    int fail_cause=-1;
    int flag = 0;

    char str[1024];
    char new[1024][80];
    char * pch;
    char full_path[512];
    if(strcmp(fd1->slocation_full_path,"/")!=0)
        {
            strcpy(full_path,fd1->slocation_full_path);
            strcat(full_path,"/");
            strcat(full_path,fd1->sfile_name);
        }
        else
        {
            strcpy(full_path,"/");
            strcat(full_path,fd1->sfile_name);
        }
       int exist = searchBst(full_path);
    //printf("in nary fd fName is %s and root data is %s\n",fd1->sfile_name,root->node_name);
    if(exist!=1){
    strcpy(str,fd1->slocation_full_path);
    pch = strtok (str,"/");
	strcpy(new[0],"/");
    while (pch != NULL)
    {
    strcpy(new[i],pch);
    i++;
    pch = strtok (NULL, "/");

    }
    while(temp)
    {
		//printf("1.in while of nary \n");
    if(rootcheck == 0)
    {

    if(strcmp(temp->node_name,new[j])==0)
    {
    prev=temp;
    temp=temp->left;
    j++;
    }
    else
    {
    //printf("Wrong path !!!");
    fail_cause = 0;
    }
    rootcheck=1;
    }


    if(temp!=NULL)
    {
		//printf("2.in temp!=null of nary \n");
    if(fail_cause==-1 && j!=i && strcmp(temp->node_name,new[j])==0)
    {
    prev=temp;
    temp=temp->left;
    j++;

    }
    else
    {
    sib=temp;
    //if(sib->node_name==fd1->sfile_name){
		//flag=1;
		//}
    temp=temp->sibling;
    }
    }
    }
    
    if(fail_cause == -1)
    {
    if(prev->left==NULL)
    {
    //create
    
    t_node *new=(t_node*)malloc(sizeof(t_node));
	new->data = (struct File_Descriptor*)malloc(sizeof(struct File_Descriptor));
strcpy(new->data->sfile_name, fd1->sfile_name);
strcpy(new->data->slocation_full_path, fd1->slocation_full_path);
new->data->sfile_type = fd1->sfile_type;
new->data->lfile_size = fd1->lfile_size;
new->data->llocation_block_no = fd1->llocation_block_no;
//printf("in nary\n \n");
//printf("fd1->sfile_name %s\n", new->data->sfile_name);
//printf("slocation_full_path %s\n", new->data->slocation_full_path);
 //   new->data = fd1;
    new->left_traversed=0;
    new->parent=prev;
    prev->left=new;
    strcpy(new->node_name,fd1->sfile_name);
    new->left=NULL;
    new->sibling=NULL;
    new->is_deleted = 0;
    }
    else if(strcmp(prev->node_name,new[i-1])==0 )
    {
	t_node *new=(t_node*)malloc(sizeof(t_node));
	new->data = (struct File_Descriptor*)malloc(sizeof(struct File_Descriptor));
strcpy(new->data->sfile_name, fd1->sfile_name);
strcpy(new->data->slocation_full_path, fd1->slocation_full_path);
new->data->sfile_type = fd1->sfile_type;
new->data->lfile_size = fd1->lfile_size;
new->data->llocation_block_no = fd1->llocation_block_no;
//printf("in nary\n \n");
//printf("fd1->sfile_name %s\n", new->data->sfile_name);
//printf("slocation_full_path %s\n", new->data->slocation_full_path);
    new->left_traversed=0;
   // new->data = fd1;
    new->parent=prev;
    sib->sibling=new;
    strcpy(new->node_name,fd1->sfile_name);
    new->left=NULL;
    new->sibling=NULL;
    new->is_deleted = 0;
    }
    else
    {
    //printf("\nWrong path !!!\nPATH --- %s \n\n\n",fd1->slocation_full_path );
    }
    }
}
else{
	//printf("Duplicate path in nary\n");
	}
    return root;
    }

int delete(struct File_Descriptor* data,t_node *root)
{
t_node *temp=root;
int rootcheck = 0;
int i = 1,pos=0,j=0,y,z;
int fail_cause=-1;
int delete_check=0;
char str[1024];
char new[1024][80];
char * pch;
if(strcmp(data->slocation_full_path,"/")!=0)
{
strcpy(str,data->slocation_full_path);
strcat(str,"/");
strcat(str,data->sfile_name);
}
else
{
strcpy(str,"/");
strcat(str,data->sfile_name);
}
//strcpy(str,data->slocation_full_path);
pch = strtok (str,"/");
strcpy(new[0],"/");
while (pch != NULL)
{ strcpy(new[i],pch);
i++;
pch = strtok (NULL, "/");
}
//printf("after while");
while((temp->left!=NULL || temp->sibling!=NULL) && j != i && fail_cause==-1) //j<i ||
{
//printf("in while %d\n", j);
if(rootcheck == 0)
{
//printf("inif temp->node_name %s,new[%d] %s\n", temp->node_name,j,new[j]);
if(strcmp(temp->node_name,new[j])==0)
{
prev=temp;
temp=temp->left;
sib=temp;
j++;
}
else
{
//printf("Wrong path !!!");
fail_cause = 0;
break;
}
rootcheck=1;
}
if(temp!=NULL)
{
if(fail_cause==-1 && j!=i && strcmp(temp->node_name,new[j])==0)
{ //printf("in temp!=null %d \n", j);
//printf("inif temp->node_name %s,new[%d] %s\n", temp->node_name,j,new[j]);
prev=temp;
temp=temp->left;
sib=temp;
j++;
}
else
{
sib=temp;
temp=temp->sibling;
}
}
else{
//printf("in fail_cause %d\n",fail_cause);
fail_cause=0;
delete_check=0;
}
}
//printf("b4 ! fail_cause %d\n",fail_cause);
if(fail_cause == -1)
{
// printf("in ! fail_cause %d\n",fail_cause);
while(temp)
{
//printf("in fail_cause while %s %s\n",temp->node_name,data->sfile_name);
if(strcmp(temp->node_name,data->sfile_name)==0)
{
//create
//printf("b4 cncting sibling to temp sibling");
sib->sibling=temp->sibling;
//printf("%s deleted \n",temp->node_name);
temp->is_deleted = TRUE;
free(temp);
delete_check=1;
break;
}
else
{
temp=temp->sibling;
}
}
if(delete_check==0){
//printf("\nWrong path !!!\nPATH --- %s \ndelete ch %d \n\n ", data->slocation_full_path,delete_check);
return 2;
}
}
else
//printf("\nWrong path !!!\nPATH --- %s \n\n\n",data->slocation_full_path);
return 10;
}

t_node* nary_insert_root()
    {
    t_node *root = (t_node*)malloc(sizeof(t_node));
	root->data = (struct File_Descriptor*)malloc(sizeof(struct File_Descriptor));
    root->left_traversed=0;
    strcpy(root->node_name,"/");
    root->left=NULL;
    root->sibling=NULL;
    root->parent=NULL;
	strcpy(root->data->sfile_name, "/");
       root->parent=NULL;
       root->is_deleted = 0;
/*****************/

strcpy(root->data->sfile_name, "/");
//printf("after filename \n");
strcpy(root->data->slocation_full_path, "");
root->data->sfile_type = 'd';
root->data->lfile_size = 0;
root->data->llocation_block_no = 0;
/***********************/
	strcpy(root->data->slocation_full_path, "/");
	//printf("root in nary insert root %s \n",root->node_name);
    return root;
    }
   
/*function for list dir*/
int list_tree_rec(t_node *root,char* harddiskpath)
    {
    t_node *temp=root;
    FILE *fp = fopen(harddiskpath, "w+" ) ;
    
    if ( fp == NULL )
	{
		//perror ("cannot open file") ;
		fclose ( fp );
		return 04;
		//exit;
	}
    temp=temp->left;
    if(temp->is_deleted == FALSE) {
      fprintf(fp,"%s \t %c\n",temp->node_name, temp->data->sfile_type);
    }
    while(temp!=root && temp!=NULL)
    {

    if(temp->left!=NULL && temp->left_traversed == 0 )
    {
		  temp=temp->left;
		  if(temp->is_deleted==0){
        fprintf(fp,"%s \t %c \n",temp->data->sfile_name, temp->data->sfile_type);
      }
    }
    else 
    {
      //t_node *temp1 = temp;
		if(temp->sibling!=NULL )
		{
		temp->left_traversed = 0;
		temp=temp->sibling;
		if(temp->is_deleted==0)
		fprintf(fp,"%s \t %c \n",temp->data->sfile_name, temp->data->sfile_type);
		}
		else
		{
		temp->left_traversed = 0;
		temp=temp->parent;
		temp->left_traversed = 1;
		}
	}
    }
    //printf("\n\n");write in file
    fclose(fp);
    return 10;
    }

int list_tree(t_node** root,int flag,char* fullpath,char* harddiskpath)
{
   t_node* retnode = NULL;
   int errcode = 10;
   if(root == NULL){}
   
   retnode = returnnode(*root,fullpath);
   if(retnode == NULL)
   {
     //printf("\nNo such node!!");
     return 01;
   }
   else
   {
		 if(retnode->left==NULL){
		 //printf("folder is empty\n");
		 }
		 else{
			 if(flag==0){
				errcode = list_tree_nonrec(retnode,harddiskpath);
			} 
			else{
				
				errcode=list_tree_rec(retnode,harddiskpath);
			}
		
		}
   }
   return errcode;
}

/*list dir non recursively*/
int list_tree_nonrec(t_node* retnode,char* harddiskpath)
{

	FILE *fp = fopen(harddiskpath, "w+" ) ;
		
	if ( fp == NULL )
	{
		//perror ("cannot open file") ;
		fclose ( fp ) ;
		return 04;
		//exit;
	}
	if(retnode->left!=NULL && retnode->left->is_deleted == FALSE)
	{
		 fprintf(fp,"%s \t %c \n",retnode->left->data->sfile_name, retnode->left->data->sfile_type);
		
	}
	else
		return 10;
	retnode=retnode->left;
	while(retnode->sibling!=NULL)
	{
		retnode = retnode->sibling;
    if(retnode->is_deleted == FALSE){
		  fprintf(fp,"%s \t %c\n",retnode->data->sfile_name, retnode->data->sfile_type);
		}
	}
	fclose(fp);
	return 10;

}
