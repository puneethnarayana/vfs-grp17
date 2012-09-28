/*************************************************************************************/
/*  C program to implement a binary search tree  */
/*************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct bst_node
{
	struct bst_node *parent;
	struct bst_node *left;
	struct bst_node *right;
	char full_path[100];
	//fd *file_desc;
}b_node;


b_node *bst_create();
/*Creates the bst, returns the root b_node*/

b_node *bst_search( b_node **bst_root_ptr, char *full_path );
int bst_intraverse(b_node *bst_root);
/*searches the BST on the basis of fullpath and returns the searched node*/
int bst_insert ( b_node **bst_root_ptr, char *data );
/* Function for creating bst */
b_node *bst_create()
{
	//printf("in bst_create \n");
	b_node *new_node = NULL;
	return new_node;
}	

/*Function for insertion of node in bst tree */
int bst_insert ( b_node **bst_root_ptr, char *data )
{
	//printf("in bst_insert \n");
	b_node *curr_node = NULL;
	int slot_found;

	char full_path[100];
           if(strcmp(data,"/")!=0)
	{strcpy(full_path,data);
	strcat(full_path,"/");
        //strcat(full_path,data);
        }
         else
           {
              strcpy(full_path,"/");
            //  strcat(full_path,data);
            }
	b_node *new_node = (b_node*) malloc( sizeof(b_node) );
	if( new_node == NULL ){
		fprintf(stderr, "bst_create_node: Unable to allocate memory\n");
		return 0;
	}
	strcpy(new_node->full_path,full_path);
	//new_node->file_desc =data;
	new_node->parent = NULL;
	new_node->left = NULL;
	new_node->right = NULL;

	if( *bst_root_ptr == NULL ){
		*bst_root_ptr = new_node;
		printf("bst_root_ptr and full path=%s \n",full_path);
		
	}
	else{
		slot_found = 0;
		curr_node = *bst_root_ptr;
		while( !slot_found ){
			if( strcmp( full_path ,curr_node->full_path) == 0 ){
				fprintf(stderr, "bst_insert: Duplicate Path %s ignored\n", full_path);
				slot_found = 1;
				return 1;
			}
	  	   else if( strcmp(curr_node->full_path,full_path) > 0 ){
				if( curr_node->left != NULL ){
					slot_found = 0;
					curr_node = curr_node->left;
				}
				else{
					slot_found = 1;
					curr_node->left = new_node;
					new_node->parent = curr_node;
					printf("left child=%s and new_node->parent->full_path=%s \n",curr_node->left->full_path,new_node->parent->full_path);
				}
			}
		  else{ /* that is, key > curr_node->key */
				if( curr_node->right != NULL ){
					slot_found = 0;
					curr_node = curr_node->right;
				}
				else{
					slot_found = 1;
					curr_node->right = new_node;
					new_node->parent = curr_node;
					printf("right child=%s and new_node->parent->full_path=%s \n",curr_node->right->full_path,new_node->parent->full_path);
				}
		   }
		}
	}
	return 0;
}
int bst_intraverse( b_node  *bst_root){

    if(bst_root!=NULL)
    {
       	b_node *curr_node = bst_root;
        bst_intraverse((curr_node)->left);
        printf("%s \n ",(curr_node)->full_path);
        bst_intraverse((curr_node)->right);
     }
     return 1;
}


b_node *bst_search( b_node **bst_root_ptr, char *full_path ){
   
    //printf("in bst_search \n");
	b_node *curr_node = NULL;
	int slot_found;
	
	if( *bst_root_ptr == NULL ){
		fprintf(stderr,"bst_search: The tree does not exists for search \n");
		return NULL;
		
	}
	else{
		slot_found = 0;
		curr_node = *bst_root_ptr;
		while( !slot_found ){
			if( strcmp( curr_node->full_path,full_path) == 0 ){
				slot_found = 1;
				//printf("in match of search\n");
				}
	  	   else if( strcmp(curr_node->full_path,full_path) > 0 ){
				if( curr_node->left != NULL ){
					//printf("in left of search got %s \n",curr_node->full_path);
					slot_found = 0;
					curr_node = curr_node->left;
				}
				else{
					fprintf(stderr,"bst_search: The searched path %s not found. \n",full_path);
					return NULL;
				}
			}
		  else{ /* that is, key > curr_node->key */
				if( curr_node->right != NULL ){
					//printf("in right of search\n");
					slot_found = 0;
					curr_node = curr_node->right;
				}
				else{
					fprintf(stderr,"bst_search: The searched path %s not found. \n",full_path);
					return NULL;
				}
		   }
		}
	}
	if(slot_found)	{
		printf("The paths %s is found \n", full_path);
		return curr_node;
		}
	else
		{fprintf(stderr,"bst_search: The searched path %s not found. \n",full_path);
		return NULL;
		}
	}

void main()
{ 
    char data[]= "/File1/Folder1/Folder.a/b.c";
    b_node *b =NULL;
    b_node *bs=NULL;
    if(b==NULL){
	b = bst_create();
	}
	
	char data4[]= "/File/Folder/Folder.a/b.c";
	//bs = bst_search( &b, data4 );
	bst_insert (&b, data );   
    char data1[]= "/File2/Folder1/Folder.a/b.c";
    bst_insert (&b, data1 );   
    char data2[]= "/File/Folder1/Folder.a/b.c";
    bst_insert (&b, data2 );   
    char data3[]= "/File/Folder2/Folder.a/b.c";
    bst_insert (&b, data3 );  
    //bs = bst_search( &b, data4 ); 
    bst_insert (&b, data4 );   
    char data7[]= "/File/Folder2/Folder.a/b.c";
    bst_insert (&b, data7 );   
    bst_intraverse(b);
    bs = bst_search( &b, "/File/Folder/Folder.a/b.c/" );
       
    if(bs==NULL){
		printf("Path not Found\n");
		}
	else{
		printf("Path is Found\n");
		}
}
