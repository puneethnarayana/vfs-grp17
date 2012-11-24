#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../include/bst.h"
#include "../include/vfs_17.h"

	static struct node* bstRoot = NULL;
    /* Add Elements to the Binary Search Tree */
    void insertBst(struct File_Descriptor *data ) {
       
        struct node* newNode = (struct node*) malloc(sizeof (struct node));
        struct node* temp;
        struct node* tempParent;
      
        char full_path[100];
        /*concatenate file name with the file path*/
        if(strcmp(data->slocation_full_path,"/")!=0)
        {
            strcpy(full_path,data->slocation_full_path);
            strcat(full_path,"/");
            strcat(full_path,data->sfile_name);
        }
        else
        {
            strcpy(full_path,"/");
            strcat(full_path,data->sfile_name);
        }
        // printf("location of data %ld", data->llocation_block_no);
        /*adding data to newNode*/
        strcpy(newNode->full_path,full_path);
        strcpy(newNode->full_path,full_path);
		//printf("ful path in node %s\n", full_path);
		newNode->fd1 = (struct File_Descriptor*)malloc(sizeof(struct File_Descriptor));
		strcpy(newNode->fd1->sfile_name, data->sfile_name);
		strcpy(newNode->fd1->slocation_full_path, data->slocation_full_path);
		newNode->fd1->sfile_type = data->sfile_type;
		newNode->fd1->lfile_size = data->lfile_size;
		newNode->fd1->llocation_block_no = data->llocation_block_no;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->parent = NULL;
        //printf("newnode data %s\n",newNode->full_path);
        if(bstRoot == NULL){
            /*if bstRoot is null,make the element bstRoot node*/
            bstRoot = newNode;
        }
        else{
            /*compare data with each node element and move to left or right child accordingly*/
            temp = bstRoot;
            tempParent = NULL;
            /*traverses to the position where new node is to be inserted*/
            while(temp){
                /*checks for the duplicate data and retuns Failure in such case*/
                /*if( strcmp( newNode->full_path ,temp->full_path) ==0 ){
                    printf("duplicate--\n");
                    temp = NULL;
                }*/

               // else{
                    /*if the data is less than the current's node data , move to left*/
                    if( strcmp( newNode->full_path ,temp->full_path) <0 ){
                        /*keeps the track of the parent node*/
                        tempParent = temp;
                        temp = temp->left;
                    }
                    else{
                        /*if the data is more than the current's node data , move to right*/
                        tempParent = temp;
                        temp = temp->right;
                    }
                //}
            }
            newNode->parent = tempParent;
           
            /*if new node's data is less than parents data,newnode is the left child*/
            if( strcmp( newNode->full_path ,tempParent->full_path) <0 ){
                tempParent->left =newNode;
               // printf (" left %s \n", newNode->full_path);
            }
            else
            {
                /*newnode is the right child*/
                tempParent->right = newNode;
                //printf (" right %s \n", newNode->full_path);
            }
        }
       // displayList();
        //return 10;
    }
   /*Inorder traversal of BST*/
    void inorder(struct node *t){
        struct node *temp;
        temp = t;
        if(temp){
            inorder(temp->left);
            //printf("\n %s \n",temp->full_path);
            inorder(temp->right);
        }
    }
  
   /*Display elements in the BST*/
    void displayList(){
        struct node *temp = bstRoot;
        if(bstRoot == NULL){
           // printf("empty tree\n");
        }
        else
            inorder(temp);
    }
     
    struct node* searchBstRec(struct node *t,char *data){
        /*if bstRoot is null or key is equal to bstRoot, return bstRoot*/
        if(t == NULL || (strcmp(data,t->full_path) ==0)){
            //printf("%s\n",t->full_path);
            //printf("%s\n",t->fd1->slocation_full_path);
            return t;
        }
        else
        {
            /*search in the right sub tree*/
            if( strcmp( data,t->full_path) <0 ){
                return searchBstRec(t->left,data);
            }
            else
            {
                /*search in the right sub tree*/
                return searchBstRec(t->right,data);
            }
         }
    }
    /* Search  Element in the List */
    int searchBst(char *data){
        struct node *t = bstRoot;
        struct node *temp = searchBstRec(t,data);
        /*if temp points to null return false else return true*/
        if(temp == NULL) {
            //printf("element is not present");
            return Failure;
        }
        else
        {
            //printf("element is present");
            return Success;
        }
    }
    
    struct node *searchBstFD(char *data){
	struct node *t = bstRoot;
	struct node *temp = searchBstRec(t,data);
	return temp;
	}
   
   
    /*transplant function for delete function. It transplants node1 with node2*/
    void transplantTree(struct node *node1,struct node *node2){
        /*if node1 is the bstRoot.Makes node2 as the bstRoot*/
        if(node1->parent == NULL){
            bstRoot = node2;
        }
        else{
            /*if node1 is the left child of its parent,replace it with node2*/
            if(node1 == node1->parent->left){
                node1->parent->left = node2;
            }
            else
            {
                /*if node1 is the right child of its parent,replace it with node2*/
                node1->parent->right = node2;
            }
        }
        if(node2 != NULL)
        {
                /*makes node1's parent as the node2's parent*/
                node2->parent = node1->parent;
        }
    }
   
   
    /* searches the minimum value node and returns the same.*/
    struct node* treeMin(struct node *m){
        while(m->left != NULL){
            m = m->left;
        }
       // printf("%s",m->full_path);
        return m;
    }
  
  
    /* Delete  Element  from the Binary Search Tree */
    void deleteBstElm(char *data){
        struct node* location;
        struct node* successor=NULL;
       
        /*Search the location of node to be deleted*/
        location = searchBstRec(bstRoot,data);
       
        /*if the element is there in the list ,deletes the same.*/
        if(location != NULL){
           // printf("element is present\n");
            /*if the node does not have a left child, transplant it with right child*/
            if(location->left == NULL){
                transplantTree(location,location->right);
            }
            else{
                    /*if the node does not have a right child, transplant it with left child*/
                    if(location->right==NULL){
                        transplantTree(location,location->left);
                    }
                    else{
                        /*If the node has both child, find the successor*/
                         successor = treeMin(location->right);
                        /*If the successor is not the child of the node to be deleted,*/
                        if(successor->parent != location){
                            /* Transplant succesor with its right child*/
                            transplantTree( successor, successor->right);
                            /*the right child of the node to be deleted is made the right child of the successor*/
                            successor->right = location->right;
                            successor->right->parent =  successor;
                        }
                        /*Transplant the node to be deleted with the successor*/
                        transplantTree(location, successor);
                        /*the left child of the node to be deleted is made the left child of the successor*/
                        successor->left = location->left;
                        successor->left->parent = successor;
                        successor->parent = location->parent;
                      
                    }
            }
            /*free the location*/
            free(location);
        }
        else
        {
            /*the element is not there in the list.*/
            //printf("element is not present\n");
        }
    }
  
    /*int main(){
      
        int location;
        char text[] = "text";
        char fileName[] = "Ruchika.txt";
        char fullPath[] = "/";
        struct File_Descriptor* data = (struct File_Descriptor*)malloc(sizeof(struct File_Descriptor));
        if(data!=NULL){
		data->lfile_size = 10;
		data -> llocation_block_no = 1;
		strcpy(data->sfile_type,text);
		strcpy(data -> sfile_name, fileName);
		strcpy(data -> slocation_full_path,fullPath);
		insertBst(data);
		}
      
        //char text1[] = "text";
        //char fileName1[] = "Alpna.txt";
        //char fullPath1[] = "/Ruchika.txt";
        //struct File_Descriptor* data1 = (struct File_Descriptor*)malloc(sizeof(struct File_Descriptor));
        //if(data1!=NULL){
        //data1->lfile_size = 10;
        //data1 -> llocation_block_no = 2;
        //data1->sfile_type = text1;
        //data1 -> sfile_name = fileName1;
        //data1 -> slocation_full_path = fullPath1;
        //insertBst(data1);
        //}
      
        printf ("List Contents: \n");
        displayList();
        printf("element search \n");
        char data8[]= "/Ruchika.txt";  
        location = searchBst(data8);
        if(location == Success){
            printf("element is present\n");
        }
        else
        {
            printf("element is not present\n");
        }
        printf("element delete:\n");
        char data9[]= "/Ruchika.txt";  
        deleteBstElm(data9);
        displayList();
      
        return 0;
    } */
