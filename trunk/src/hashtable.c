#include<stdio.h>
#include<stdlib.h>
#include "../include/main.h"
#include "../include/hashtable.h"
#include "../include/linkedlist.h"
//a-z & A-Z
#define MAXNODE 52

//initialising hash table with null entry
void initialzeHashTable(struct Hash_Table *ht)
{
	int i;
	for( i=0;i<MAXNODE;i++)
		ht->Table[i]=NULL;

}

//creating hash key
int hashFunction(char c)
{
int value= (int)c;
if((value>=65) & (value<=90))
 return ((value%65)+26);
else
  return (value%97);
}

//inserting into hash table
void insertHashTable(struct Hash_Table *ht, struct File_Descriptor *fd1)
{
char c=fd1->sfile_name[0];
int key=hashFunction(c);
//printf("inside insert, key: %d\n",key);
ht->Table[key]=listInsertStart(ht->Table[key],fd1->sfile_name,fd1);
}

//searching for hash location
List_Node *searchHashTable(struct Hash_Table *ht, char* filename) {
	List_Node *start;
	char c = filename[0];
	int key = hashFunction(c);
	start = ht->Table[key];
	//printf("inside search, key: %d\n",key);
	//printf("inside search, %s\n", start->data->sfile_name);
	return listSearchStrKey(start, filename);

}

//deleting hash table entry
void deleteHashTable(struct Hash_Table *ht, char* filename) {
	char c = filename[0];
	int key = hashFunction(c);
	ht->Table[key] = listDeleteNode(ht->Table[key], filename);
}

