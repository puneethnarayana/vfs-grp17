#include<stdio.h>
#include "../include/main.h"
#include "../include/bst.h"
#include "../include/hashtable.h"
#include "../include/linkedlist.h"
#include "../include/narray.h"
#include <string.h>


void bitMapInit();
long freeLocation();
void bitmapUpdate(long, int);
//global variables
struct Main_Header m1; 
struct Block b1;
struct File_Descriptor fd1;
struct Free_List fl1;
FILE *fptr; // pointer to the file object	
	
/* function for creating the large binary file for VFS */
void createVFS(char *name, long size) {
	int i=1, j=1; //loop variable for creating file descritors and file blocks
	
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
     
	
	fptr = fopen(name, "wb+"); // opening the file with given label in binary write mode
	if(fptr == NULL) {
		printf("Error in Creating VFS");
	}
	else {
		long first_loc_fblock = ftell(fptr);
		m1.freedescriptor = 1 + (first_loc_fblock + (sizeof(m1)));
		m1.freeblock = 1 + (m1.freedescriptor  + m1.ltotal_file_descriptors*sizeof(fd1));   
		//printf("\n%ld", m1.freedescriptor);
		//printf("\n%ld", m1.freeblock);
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

void mount_VFS(char *name) {
	printf("\n--------------------Initializing Bitmap\n");
	bitMapInit();
	printf("\n--------------------Bitmap Initialized\n");
	printf("\n--------------------VFS Mounting\n");
	fptr = fopen(name, "rb+"); // opening file for read/write
	if(fptr == NULL) {
		printf("\nError in Mounting VFS\n");
		fclose(fptr);
	}
	
	else {
		fclose(fptr);
		printf("\n--------------------VFS Mounted\n");
	}
}

void unmount_VFS() {
	printf("\n--------------------Unmounting VFS\n");
	//fclose(fptr);
	free(fl1.bitmap);
	printf("\n--------------------VFS Unmounted\n");
}	


void write_File(char *name) {
	char file_name[50];  
	char ch,arr[1024];
	
	fptr = fopen(name, "rb+"); // opening file for read/write
	//printf("%ld", m1.freeblock);
	//SEND pointer to the first location of the file block
	//printf("before seek");
	fseek(fptr,m1.freeblock,SEEK_SET);
	//printf("after seek");
	//getting the first free location from the Bitmap
	long a = freeLocation();
	//printf("%ld",a);
	//Pointing the pointer to the first file block to start writing
	fseek(fptr,a*sizeof(b1),SEEK_CUR);

	//Write files to the file system
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
	//printf("before write");
	fwrite(&arr, sizeof(arr), 1, fptr);
	
	//printf("after write");
	//fclose(fwptr);	
	//Sending pointer to write at the first location of the FDescript
	fseek(fptr,m1.freedescriptor,SEEK_SET);
	fseek(fptr,a*sizeof(fd1),SEEK_CUR);
	fd1.sfile_name = file_name;
	//fd1.slocation_full_path[250];
	//fd1.sfile_type;
	fd1.lfile_size = sizeof(arr);
	fd1.llocation_block_no = a;
	fwrite(&fd1, sizeof(fd1), 1, fptr);
	//Update bit map by passing block no. of occupied block
	bitmapUpdate(a, 1);
	fclose(fptr);
}

void delete_File() {

}

/*writing code for bit map.*/
//Initializing bitmap to zero
void bitMapInit() {
	fl1.bitmap = (char*)calloc(m1.ltotal_file_descriptors, sizeof(char));
	long i;
	for(i=0;i < m1.ltotal_file_descriptors;i++){
		if(fd1.llocation_block_no == -9999)
				fl1.bitmap[i] = 0;
		else
			fl1.bitmap[i] = 1;
	}
}

// returns free bitmap location
long freeLocation() {
	long free_loc;
	//fl1.bitMap[0]=1;
	long j;
	for(j=0;j < m1.ltotal_file_descriptors;j++){
		if(fl1.bitmap[j]==0){
			free_loc = j;
			break;
		}
	}
	if(j==m1.ltotal_file_descriptors){
		printf("Disk is full");
	}
	return free_loc;
}

//updating occupied bit map
void bitmapUpdate(long n, int flag){
	if (flag ==1 )
	fl1.bitmap[n]=1;	
	else
	fl1.bitmap[n]=0;		
}

void stats(char *name)
{
		fptr = fopen(name, "rb+");
		fread(&m1, sizeof(m1), 1, fptr);
		printf("\nMount Label: %s", m1.sfile_system_label);
		printf("\nNext Free File Descriptor Location :%ld", m1.freedescriptor * (freeLocation() + 1));
		printf("\nNext Free Block Location: %ld", m1.freeblock * (freeLocation() + 1));
		printf("\nTotal File Blocks: %ld", m1.ltotal_file_blocks);
		printf("\nAvailable File Blocks: %ld", m1.ltotal_file_blocks - freeLocation());
		printf("\nTotal File Descriptors: %ld", m1.ltotal_file_descriptors);
		printf("\nAvailable File Descriptors: %ld\n", m1.ltotal_file_descriptors - freeLocation());
		
		fread(&fd1, sizeof(fd1), 1, fptr);
		fclose(fptr);
}
