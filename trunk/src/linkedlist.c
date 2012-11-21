#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/linkedlist.h"
#include "../include/vfs_17.h"

void printlist(List_Node*);
//
List_Node *listInsertStart( List_Node *head, char* key, struct File_Descriptor* data) {	
    List_Node *start;
    //start = (List_Node*)malloc(sizeof(List_Node *));
    //start->data = data;
    //change
    start = (List_Node*)malloc(sizeof(List_Node *));
	start->data = (struct File_Descriptor*)malloc(sizeof(struct File_Descriptor));
	strcpy(start->data->sfile_name, data->sfile_name);
	strcpy(start->data->slocation_full_path, data->slocation_full_path);
	start->data->sfile_type = data->sfile_type;
	start->data->lfile_size = data->lfile_size;
	start->data->llocation_block_no = data->llocation_block_no;
    //change
    
    start->key = key;
    //printf("inside linkedlistinsert, %s\n", start->key);
    //printf("inside linkedlistinsert, %s\n", start->data->slocation_full_path);
    //printf("inside linkedlistinsert, %s\n", start->data->sfile_name);
    start->next = head;
    return start;	
}

//
List_Node *listSearchStrKey( List_Node *head, char *key ) {
List_Node *returnlist;	
//char arr[100];
	while(head!=NULL) {
		//strcpy(arr, strstr(head->data->sfile_name, key));
		//printf("%s\n",arr);
		//printf("inside linkedlistsearch, %s\n", head->data->sfile_name);
		if (strncmp(head->data->sfile_name, key, strlen(key)) == 0) {
		//printf("returning data\n");
		//if(strcmp(strstr(head->data->sfile_name, key), head->data->sfile_name) == 0) {
			
		returnlist = listInsertStart(returnlist, head->key, head->data);
		}
		head=head->next;
	}
	if (returnlist != NULL) {
		return returnlist;
	}
	else {
		return NULL;
//printf("returning null\n");
	}
}

//
void listDeleteNode( List_Node *head, char *key, char *path )
{
	//printf("inside linkedlist key = %s path = %s\n", key, path);
	//printlist(head);
    List_Node *current, *prev;
    /*if (head == NULL)
    {
        return NULL;
    } */
    prev = NULL;
    current = head;
    //printf("inside linkedlist delete %s %s\n", current->key, current->data->slocation_full_path);
    while(current != NULL){
		//printf("inside linkedlist delete %s %s\n", current->data->sfile_name, current->data->slocation_full_path);
        if (strcmp(current->data->sfile_name, key) == 0 && strcmp(current->data->slocation_full_path, path) == 0)
        {
			//printf("before free");
            /*if (prev == NULL)
            { */
				//new_head = head->next;
				//free(head);
				//return new_head;            
			//}
            //prev->next=current->next;
            free(current);
            //printf("after free");
            break;
        }
        prev = current;
        //printf("inside linkedlist delete %s %s\n", prev->key, prev->data->slocation_full_path);
        current = current->next;
        //printf("inside linkedlist delete %s %s\n", current->key, current->data->slocation_full_path);
    } //printlist(head);
    //return head;
}

//prints the linkedlist
void printlist(List_Node* head) {
	List_Node *start = head;
	while(start != NULL) {
		printf("%s->%s\n", start->data->sfile_name, start->data->slocation_full_path);
		start=start->next;
	}
}
