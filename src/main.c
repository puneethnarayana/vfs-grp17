#include<stdio.h>
#include "../include/main.h"
#include "../include/bst.h"
#include "../include/hashtable.h"
#include "../include/linkedlist.h"
#include "../include/narray.h"

void createVFS(char *name, long size) {
struct Main_Header m1;
struct Block b1;
struct File_Descriptor fd1;
b1.lfixed_size_buffer = 10240;
m1.sfile_system_label = name;
m1.lsize = size - sizeof(m1);
m1.ltotal_file_descriptors = (m1.lsize)/(sizeof(fd1) + b1.lfixed_size_buffer);

printf("--------------------Creating VFS-----------------------------");
printf("\nvfs name : %s", m1.sfile_system_label);
printf("\nmeta size : %d", sizeof(m1));
printf("\nsize left after meta: %ld", m1.lsize);
printf("\ntotal file desc : %ld", m1.ltotal_file_descriptors);
printf("\nsize of file descriptor : %d", sizeof(fd1));
m1.lsize = size - (m1.ltotal_file_descriptors * sizeof(fd1));
printf("\nsize left after fd: %ld", m1.lsize);
m1.lsize = size - (m1.ltotal_file_descriptors * b1.lfixed_size_buffer);
printf("\nsize left after file block: %ld\n", m1.lsize);
/*
char *sfile_system_label;
long lsize;
long ltotal_file_descriptors;
long lused_file_descriptors;
struct File_Descriptor *cpfile_descriptor;
struct Free_List *cpfree_list; */

FILE *fptr;
fptr = fopen(name, "wb+");
if(fptr == NULL) {
	printf("Error in Creating VFS");
}
else {
	
	fwrite(&m1, sizeof(m1), 1, fptr); // writing meta header
	printf("meta header created\n");
		
	fwrite(&fd1, sizeof(fd1), m1.ltotal_file_descriptors, fptr); // writing file descriptor
	printf("file  descriptor created\n");
	
	fwrite(&b1, b1.lfixed_size_buffer, m1.ltotal_file_descriptors, fptr); // writing file block
	printf("file block created\n");

	
	fclose(fptr);
}
}
