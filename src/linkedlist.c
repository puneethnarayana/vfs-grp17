#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/linkedlist.h"
#include "../include/main.h"

//
List_Node *listInsertStart( List_Node *head, char* key, struct File_Descriptor* data) {	
    List_Node *start;
    start = (List_Node*)malloc(sizeof(List_Node *));
    start->data = data;
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
while(head!=NULL) {
//printf("inside linkedlistsearch, %s\n", head->data->sfile_name);
if (strcmp(head->data->sfile_name, key) == 0) {
		//printf("returning data\n");
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
List_Node *listDeleteNode( struct List_Node *head, char *key)
{
    struct List_Node *prev, *current, *new_head;
    if (head == NULL)
    {
        return NULL;
    }
    prev = NULL;
    current = head;
    while(current != NULL){
        if (strcmp(head->key, key)==0)
        {
            if (prev == NULL)
            {
     		new_head = head->next;
    		free(head);
    		return new_head;            
         }
            prev->next=current->next;
            free(current);
            break;
        }
        prev = current;
        current = current->next;
    }
    return head;
}

//prints the linkedlist
void printlist(List_Node* head) {
	List_Node *start = head;
	while(start != NULL) {
		printf("%s->%s\n", start->data->sfile_name, start->data->slocation_full_path);
		start=start->next;
	}
}
