#include<stdio.h>
#include<stdlib.h>
#include "../include/vfs_17.h"
#include "../include/hashtable.h"
#include "../include/linkedlist.h"
//a-z & A-Z
#define MAXNODE 53

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
	//printf("%c\n", c);
int value= (int)c;
//printf("%d\n", value);
if((value>=65) && (value<=90))
 return ((value%65)+26);
else if((value>=97) && (value<=122)) 
  return (value%97);
else
	return 53;
}



//inserting into hash table
void insertHashTable(struct Hash_Table *ht, struct File_Descriptor *fd1)
{
char c=fd1->sfile_name[0];
int key=hashFunction(c);
//printf("inside insert, key: %d\n",key);
ht->Table[key]=listInsertStart(ht->Table[key],fd1->sfile_name,fd1);
//printlist(ht->Table[key]);
}

//searching for hash location
List_Node *searchHashTable(struct Hash_Table *ht, char* filename) {
	//printf("%s\n", filename);

	List_Node *start;
	char c = filename[0];
	int key = hashFunction(c);
	start = ht->Table[key];
	//printlist(ht->Table[key]);
	//printf("inside search, key: %d\n",key);
	//printf("inside search, %s\n", start->data->sfile_name);
	return listSearchStrKey(start, filename);

}

//deleting hash table entry
void deleteHashTable(struct Hash_Table *ht, char* filename, char* filepath) {
	char c = filename[0];
	int key = hashFunction(c);
	//printf("inside hash %s %s\n", filename, filepath);
	listDeleteNode(ht->Table[key], filename, filepath);
	//printlist(ht->Table[key]);
}

