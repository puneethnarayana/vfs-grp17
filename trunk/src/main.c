#include<stdio.h>
#include "../include/main.h"
#include "../include/bst.h"
#include "../include/hashtable.h"
#include "../include/linkedlist.h"
#include "../include/narray.h"

/* function for creating the large binary file for VFS */

void createVFS(char *name, long size) {
	int i=1, j=1; //loop variable for creating file descritors and file blocks
	struct Main_Header m1; 
	struct Block b1;
	struct File_Descriptor fd1;
	printf("--------------------Creating VFS-----------------------------");
	
	m1.sfile_system_label = name;  //storing the VFS label
	printf("\nvfs name : %s", m1.sfile_system_label);
	printf("\nsize of meta header: %d", sizeof(m1));
	m1.lsize = size - sizeof(m1); // size remaining after creation of meta header 
	
	printf("\nsize left after ceation of meta header: %ld", m1.lsize);
	m1.ltotal_file_descriptors = (m1.lsize)/(sizeof(fd1) + sizeof(b1)); // calculating the no. of file descriptors can be used in remaining space
	//m1.ltotal_file_descriptors = 100; // calculating the no. of file descriptors can be used in remaining space
	printf("\nsize of each file descriptor : %d", sizeof(fd1));
	printf("\ntotal file descriptors : %ld", m1.ltotal_file_descriptors);
    m1.lsize = m1.lsize - (m1.ltotal_file_descriptors * sizeof(fd1)); // size remaining after creation of file descriptors
    
    printf("\nsize left after creation of file descriptors: %ld", m1.lsize);
    m1.ltotal_file_blocks = (m1.lsize)/(sizeof(b1)); // calculating the no. of file blocks can be used in remaining space
    //b1.ltotal_file_blocks = 100; // calculating the no. of file blocks can be used in remaining space
  
    printf("\nsize of each file block : %d", sizeof(b1));
    printf("\ntotal file blocks : %ld", m1.ltotal_file_blocks);
    m1.lsize = m1.lsize - (m1.ltotal_file_blocks * sizeof(b1)); // calculating the space unused 
	
	printf("\nsize left after creation of file block: %ld\n", m1.lsize);
    
    /* wrting large binary file of given size including the 
     * 1.meta header
     * 2.file descriptor and
     * 3.file block
     */
     
	FILE *fptr; // pointer to the file object
	fptr = fopen(name, "wb+"); // opening the file with given label in binary write mode
	if(fptr == NULL) {
		printf("Error in Creating VFS");
	}
	else {
		fwrite(&m1, sizeof(m1), 1, fptr); // writing meta header
		printf("\nmeta header created\n");
		for (; i<= m1.ltotal_file_descriptors; i++) {
			fwrite(&fd1, sizeof(fd1), 1, fptr); // writing file descriptors
		}
		printf("file  descriptor created\n"); 
	
	   for (; j<= m1.ltotal_file_blocks; j++) {
			fwrite(&b1, sizeof(b1), 1, fptr); // writing file blocks
		}
		printf("file block created\n"); 
		fclose(fptr); // closing the file to store it in persistent memory
	}
}
