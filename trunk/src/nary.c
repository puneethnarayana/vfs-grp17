#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#include "../include/nary.h"
#include "../include/vfs_17.h"
#include "../include/bst.h"

#define TRUE 1
#define FALSE 0
void pathchange(t_node **root);
t_node* getchild(t_node **node);
void delete_nodes(t_node *node);

//function to return the searched node
t_node* returnnode(t_node **root,char *fullpath)
{
	int n, i,j,count = 1,c;
	char **new;
	char spath[200];
	int flag = 1;

	t_node *retnode;
	if(*root == NULL)
	{
		
		return 0;
	}

	strcpy(spath,fullpath);
	n = strlen(spath);
	if(n==1)
		count = 1;
	else
	{
	for(i=1;i<n;i++){
		if(spath[i]=='/')
			count++;
	}
		count++;
	}
             
	(new) = (char **)malloc(sizeof(char*)*count);
        i = 0;
	for(c=0;c<count;c++)
	{
		j = 0;
		new[c] = (char *)malloc(sizeof(char) * 50);
		while(spath[i] != '/' && spath[i]!='\0')
		{
			new[c][j] = spath[i];
			i++;
			j++;
		}
		i++;
		new[c][j] = '\0';
	}

	new[0][0] = '/';
	new[0][1] = '\0';
        i = 0;
	retnode = *root;
       while(retnode != NULL)
	{          
		if(retnode->is_deleted == 0 && strcmp(retnode->data->sfile_name,new[i]) == 0)
		{
			i++;
                       if(i == count)
				{
                 break;
				}
			retnode = retnode->left;
			
		}
		
		else if(retnode->sibling != NULL)
		{
			retnode = retnode->sibling;
		}
		else
		{
			flag =0;
			break;
		}
	}
     
	
	if(flag == 0 || retnode == NULL)
	{
		
		return NULL;
	}
        
	return (retnode);
	}


int move_node(t_node* root,char* source_path,char* destination_path)
 {
	
 
  char temppath[100],tempfname[100];

  strcpy(temppath,source_path);

 
 	
 	t_node *temp = root;
        t_node *temp1 = root;
        t_node *temp3,*temp4,*temp5;
	
 	t_node *node = returnnode(&temp,source_path);
   strcpy(tempfname,node->data->sfile_name);
       
 	//printf("dhgjh%s\n", tempfname);
 	t_node *node2 = returnnode(&temp1,destination_path);
        //printf("returned") 
         
     //printf("egserger%s\n", node2->data->sfile_name);
 

 	if(node->is_deleted == TRUE || node2->is_deleted == TRUE)
     {
    		
     	return -1;
   	}

	//if(node->parent == node2)
	//{return 3;}
	
 	int i=0;
//checking if any of the path is not existing
  if(node!=NULL && node2!=NULL)
  {
    		temp4=node->parent;
		if(temp4->left==node)
		{
		      temp4->left=node->sibling;
		      node->sibling=NULL;
	    	}
              else
    	      {
      		temp5=temp4->left;
		      while(temp5->sibling!=node)
		      {
			temp5=temp5->sibling;
		      }
	      temp5->sibling=node->sibling;
	      node->sibling=NULL;
              }
    //getting the node to from where it has to be moved

temp3=getchild(&node2); 
    if(temp3==NULL)
    {
	      node2->left=node;
	      node->parent=node2;
	      char c[100];
      //copying the full path for root


      if(strcmp(node2->data->slocation_full_path,"/")==0)
      {
			strcpy(c,"/");
			strcat(c,node2->data->sfile_name);
			strcpy(node->data->slocation_full_path,c);
      }
       //copying for the other nodes
      else
      {
        
			strcpy(c,node2->data->slocation_full_path);
			strcat(strcat(c,"/"),node2->data->sfile_name);
			strcpy(node->data->slocation_full_path,c);
      }
      
    }
    else
    {
	      
	      temp3->sibling=node;
	      node->parent=temp3->parent;
	      strcpy(node->data->slocation_full_path,temp3->data->slocation_full_path);
	      
	    }
    
   
    
    delete_nodes(node->left);
    char a[200],b[200];
    strcpy(a,temppath);
    if(strcmp(a,"/")==0)
   
    deleteBstElm(tempfname);
    else
    {
	      int i=0;
	      strcpy(b,"\0");
	      strcpy(b,a);
	      strcat(strcat(b,"/"),tempfname);
	      
              deleteBstElm(b);
    }
    insertBst(node->data); 
    pathchange(&node);
    
     return 1;
  }
 	
 	
 	 
 }

void pathchange(t_node **root)
{
  t_node *temp1=*root,*temp=*root;
  if(root!=NULL)
  	{
    		if(temp1->left!=NULL)
    		{
		      temp=temp1;
		      temp1=temp1->left;
		      
		      deleteBstElm(temp1->data->slocation_full_path);
		      temp1->parent=temp;
		      char res[100];
			      if(strcmp(temp->data->slocation_full_path,"/")==0)
			      {
					strcpy(res,temp->data->slocation_full_path);
					strcpy(temp1->data->slocation_full_path,strcat(res,temp1->parent->data->sfile_name));
			      }
			      else
			      {
				      strcpy(res,temp->data->slocation_full_path);
				      strcpy(temp1->data->slocation_full_path,strcat(strcat(res,"/"),temp1->parent->data->sfile_name));
			      }
		      insertBst(temp1->data );
		      pathchange(&temp1);
    }
    
      while(temp1->sibling!=NULL)
      {
        temp=temp1;
        temp1=temp1->sibling;
        temp1->parent=temp->parent;
        char res[100];
				strcpy(res,temp->data->slocation_full_path);
				strcpy(temp1->data->slocation_full_path,temp->data->slocation_full_path);
        //inserttree(cnode->data);
        pathchange(&temp);
      }
  }
  return;
} 
t_node* getchild(t_node **node)
{
       t_node *temp=*node;
  		if(temp->left==NULL)
  			return NULL;
  
 		 else{
    			temp=temp->left;
    			while(temp->sibling!=NULL)
    				{
      					temp=temp->sibling;
   				 }
    				return(temp);
   	 } 
}
void delete_nodes(t_node *node)
{       char path[200];
  if(node!=NULL)
  {
  
  delete_nodes(node->left);
  //copying the path
  strcpy(path,node->data->slocation_full_path);
  if(strcmp(path,"/")==0)
        deleteBstElm(node->data->slocation_full_path);
  
 	 else
  	{
    			strcat(strcat(path,"/"),node->data->sfile_name);
               			 deleteBstElm(path);
    
 	 }
  delete_nodes(node->sibling);
  }
  return ;
}

    
    void printtree(t_node *root)
    {
    t_node *temp=root;
    //printf("----------retnode VFS Structure----------\n\n%s",temp->node_name);
    temp=temp->left;
    printf("\n%s",temp->data->sfile_name);
    while(temp!=root && temp!=NULL)
    {

    if(temp->left!=NULL && temp->left_traversed == 0 )
    {
		//printf("\nLeft of - %s",temp->data->sfile_name);
		temp=temp->left;
		if(temp->is_deleted==0) {}
		printf("\nLeft - %s",temp->data->sfile_name);
    }
    else 
    {
		if(temp->sibling!=NULL )
		{
		temp->left_traversed = 0;
		printf("\nsibling of - %s",temp->data->sfile_name);
		temp=temp->sibling;
		if(temp->is_deleted==0) {}
		printf("\nsibling - %s",temp->data->sfile_name);
		}
		else
		{
		temp->left_traversed = 0;
		temp=temp->parent;
		temp->left_traversed = 1;
		}
	}
    }
    printf("\n\n");
    }
    

    t_node* insert_node (struct File_Descriptor* fd1,t_node *root)//change return type to int, parameter: FD
    {
    t_node *temp=root;
    int rootcheck = 0;
    int i = 1,pos=0,j=0,y,z;
    int flag1=-1;
    int flag = 0;

    char str[1024];
    char new[1024][80];
    char * starray;
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
    starray = strtok (str,"/");
	strcpy(new[0],"/");
    while (starray != NULL)
    {
    strcpy(new[i],starray);
    i++;
    starray = strtok (NULL, "/");

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
    flag1 = 0;
    }
    rootcheck=1;
    }


    if(temp!=NULL)
    {
		//printf("2.in temp!=null of nary \n");
    if(flag1==-1 && j!=i && strcmp(temp->node_name,new[j])==0)
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
    
    if(flag1 == -1)
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

	  new->left_traversed=0;
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
int flag1=-1;
int delete_check=0;
char str[1024];
char new[1024][80];
char * starray;
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
starray = strtok (str,"/");
strcpy(new[0],"/");
while (starray != NULL)
{ strcpy(new[i],starray);
i++;
starray = strtok (NULL, "/");
}
//printf("after while");
while((temp->left!=NULL || temp->sibling!=NULL) && j != i && flag1==-1) //j<i ||
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
flag1 = 0;
break;
}
rootcheck=1;
}
if(temp!=NULL)
{
if(flag1==-1 && j!=i && strcmp(temp->node_name,new[j])==0)
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
//printf("in flag1 %d\n",flag1);
flag1=0;
delete_check=0;
}
}
//printf("b4 ! flag1 %d\n",flag1);
if(flag1 == -1)
{
// printf("in ! flag1 %d\n",flag1);
while(temp)
{
//printf("in flag1 while %s %s\n",temp->node_name,data->sfile_name);
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
  int errcode;
   if(root == NULL){}
   
   retnode = returnnode(root,fullpath);
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
