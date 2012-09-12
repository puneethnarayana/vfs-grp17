#include<stdio.h>
#include "../include/main.h"
#include "../include/bst.h"
#include "../include/hashtable.h"
#include "../include/linkedlist.h"
#include "../include/narray.h"
#include <string.h>

/* function for creating the large binary file for VFS */
void bitMapInit();
long freeLocation();
void bitmapUpdate(long, int);

void createVFS(char *name, long size) {
	int i=1, j=1; //loop variable for creating file descritors and file blocks
	struct Main_Header m1; 
	struct Block b1;
	struct File_Descriptor fd1;
	struct Free_List fl1;
	printf("--------------------Creating VFS-----------------------------");
	
	m1.sfile_system_label = name;  //storing the VFS label
	printf("\nvfs name : %s", m1.sfile_system_label);
	printf("\nsize of meta header: %d", sizeof(m1));
	m1.lsize = size - sizeof(m1); // size remaining after creation of meta header 
	
	//printf("\nsize left after ceation of meta header: %ld", m1.lsize);
	m1.ltotal_file_descriptors = (m1.lsize)/(sizeof(fd1) + sizeof(b1)); // calculating the no. of file descriptors can be used in remaining space
	
	printf("\nsize of each file descriptor : %d", sizeof(fd1));
	printf("\ntotal file descriptors : %ld", m1.ltotal_file_descriptors);
    m1.lsize = m1.lsize - (m1.ltotal_file_descriptors * sizeof(fd1)); // size remaining after creation of file descriptors
    
    //printf("\nsize left after creation of file descriptors: %ld", m1.lsize);
    m1.ltotal_file_blocks = (m1.lsize)/(sizeof(b1)); // calculating the no. of file blocks can be used in remaining space
    
  
    printf("\nsize of each file block : %d", sizeof(b1));
    printf("\ntotal file blocks : %ld", m1.ltotal_file_blocks);
    m1.lsize = m1.lsize - (m1.ltotal_file_blocks * sizeof(b1)); // calculating the space unused 
	
	printf("\nspace unsed: %ld\n", m1.lsize);
    
     
		
    /* wrting the large binary file of given size including- 
     * 1.meta header
     * 2.file descriptors and
     * 3.file blocks
     */
     
	FILE *fptr; // pointer to the file object
	fptr = fopen(name, "wb+"); // opening the file with given label in binary write mode
	if(fptr == NULL) {
		printf("Error in Creating VFS");
	}
	else {
		
		long last_loc_fblock = ftell(fptr);
		m1.freeblock = 1 + (last_loc_fblock - (m1.ltotal_file_blocks*sizeof(b1))); 
		m1.freedescriptor =  m1.freeblock - (m1.ltotal_file_descriptors*sizeof(fd1));
		
		// writing meta header
		fwrite(&m1, sizeof(m1), 1, fptr); 
		printf("\nmeta header created\n");
	    
	    fd1.llocation_block_no = -9999;
	    // writing file descriptors
		for (; i<= m1.ltotal_file_descriptors; i++) {
			fwrite(&fd1, sizeof(fd1), 1, fptr); 
		}
		printf("file  descriptor created\n"); 
	    // writing file blocks
	    for (; j<= m1.ltotal_file_blocks; j++) {
			fwrite(&b1, sizeof(b1), 1, fptr); 
		}
		printf("file block created\n"); 
		fclose(fptr); // closing the file to store it in persistent memory
		printf("\n--------------------VFS Created-----------------------------\n");
	}
}

FILE* mount_VFS(char *name) {
	printf("\n--------------------Initializing Bitmap\n");
	bitMapInit();
	printf("\n--------------------Bitmap Initialized\n");
	printf("\n--------------------VFS Mounting\n");
	FILE *fptr; // pointer to the file object
	fptr = fopen(name, "rb+"); // opening the file for update
	if(fptr == NULL) {
		printf("\nError in Mounting VFS\n");
		return NULL;
	}
	else {
		printf("\n--------------------VFS Mounted\n");
		return fptr;
	}
}

void unmount_VFS(char *name, FILE *fptr) {
	printf("\n--------------------Unmounting VFS\n");
	fclose(fptr);
	printf("\n--------------------VFS Unmounted\n");
}	


void write_File(char *name) {
	FILE *fwptr;
	char file_name[50];
	struct Main_Header m1;
	struct File_Descriptor fd1;
	struct Block b1;  
	char ch,arr[1024];
	fwptr = fopen(name,"w+");	
	//SEND pointer to the first location of the file block
	//printf("before seek");
	fseek(fwptr,m1.freeblock,SEEK_SET);
	//printf("after seek");
	//getting the first free location from the Bitmap
	long a = freeLocation();
	//Pointing the pointer to the first file block to start writing
	fseek(fwptr,a*sizeof(b1),SEEK_CUR);
	//Write files to the file system
	if(fwptr == NULL)
		printf("error\n");
	else{
		printf("Enter the Name of file: \n");
		scanf("%s", file_name);
		printf("Enter the data to be written to file and press $ to indicate the end of file\n");
		int i=0;
		do
		{
			arr[i]=ch;
			//printf("%c",arr[i]);
			ch=getchar();
			i++;
		} while (ch!='$');
	printf("before write");
	fwrite(&arr, sizeof(arr), 1, fwptr);
	printf("after write");
	//fclose(fwptr);
	}	
	//Sending pointer to write at the first location of the FDescript
	fseek(fwptr,m1.freedescriptor,SEEK_SET);
	fd1.sfile_name = file_name;
	//fd1.slocation_full_path[250];
	//fd1.sfile_type;
	fd1.lfile_size = sizeof(arr);
	fd1.llocation_block_no = a;
	fwrite(&fd1, sizeof(fd1), 1, fwptr);
	//Update bit map by passing block no. of occupied block
	
	bitmapUpdate(a, 1);
	fclose(fwptr);
}

void delete_File() {

}

/*writing code for bit map.*/
//Initializing bitmap to zero
void bitMapInit() {
	struct Main_Header m1;
	struct Free_List fl1;
	struct File_Descriptor fd1;
	fl1.bitmap = (char*)calloc(m1.ltotal_file_blocks, sizeof(char));
	int i;
	for(i=0;i < m1.ltotal_file_blocks;i++){
		if(fd1.llocation_block_no == -9999)
				fl1.bitmap[i] = 0;
		else
			fl1.bitmap[i] = 1;
	}
}

// returns free bitmap location
long freeLocation() {
	long free_loc;
	struct Main_Header m1;
	struct Free_List fl1;
	//fl1.bitMap[0]=1;
	long j;
	for(j=0;j < m1.ltotal_file_blocks;j++){
		if(fl1.bitmap[j]==0){
			free_loc = j;
			break;
		}
	}
	if(j==m1.ltotal_file_blocks){
		printf("Disk is full");
	}
	return free_loc;
}

//updating occupied bit map
void bitmapUpdate(long n, int flag){
	struct Free_List fl1;
	if (flag ==1 )
	fl1.bitmap[n]=1;	
	else
	fl1.bitmap[n]=0;		
}
