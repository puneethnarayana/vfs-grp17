#include<stdio.h>
#include "../include/main.h"
//#include "../include/bst.h"
#include "../include/hashtable.h"
#include "../include/linkedlist.h"
#include "../include/nary.h"
#include <string.h>
#include <stdlib.h>

//global variables
struct Main_Header m1; 
struct Block b1;
struct File_Descriptor fd1;
struct Free_List fl1;
struct Hash_Table ht1;
struct List_Node *ln1;
t_node *root = NULL;
FILE *fptr; // pointer to the file object	

int search_File(char*, char*);
	
/* function for creating the large binary file for VFS */
void create_VFS(char *name, long size) {
	int i=1, j=1; //loop variable for creating file descritors and file blocks
	
	printf("--------------------Creating VFS-----------------------------");
	
	m1.sfile_system_label = name;  //storing the VFS label
	printf("\nvfs name : %s", m1.sfile_system_label);
	printf("\nsize of meta header: %ld", sizeof(m1));
	m1.lsize = size - sizeof(m1); // size remaining after creation of meta header 
	
	//printf("\nsize left after ceation of meta header: %ld", m1.lsize);
	m1.ltotal_file_descriptors = (m1.lsize)/(sizeof(fd1) + sizeof(b1)); // calculating the no. of file descriptors can be used in remaining space
	
	printf("\nsize of each file descriptor : %ld", sizeof(fd1));
	printf("\ntotal file descriptors : %ld", m1.ltotal_file_descriptors);
    m1.lsize = m1.lsize - (m1.ltotal_file_descriptors * sizeof(fd1)); // size remaining after creation of file descriptors
    
    //printf("\nsize left after creation of file descriptors: %ld", m1.lsize);
    m1.ltotal_file_blocks = (m1.lsize)/(sizeof(b1)); // calculating the no. of file blocks can be used in remaining space
    
  
    printf("\nsize of each file block : %ld", sizeof(b1));
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
		//long first_loc_fblock = ftell(fptr);
		m1.freedescriptor = 1 + (sizeof(m1));
		m1.freeblock = 1 + (m1.freedescriptor  + m1.ltotal_file_descriptors*sizeof(fd1));   
		//printf("\n%ld", m1.freedescriptor);
		//printf("\n%ld", m1.freeblock);
		// writing meta header
		fwrite(&m1, sizeof(m1), 1, fptr); 
		printf("\nmeta header created\n");
	    
	    //file descriptor default values
	    fd1.llocation_block_no = -9999;
	    fd1.lfile_size = 0;
	    //strcpy(fd1.sfile_name,"bcd");
	    //fd1.sfile_type = 'f';
	    //strcpy(fd1.slocation_full_path, "\null\null");
	    // writing file descriptors
	    fseek(fptr,m1.freedescriptor,SEEK_SET);
		for (; i<= m1.ltotal_file_descriptors; i++) {
			fwrite(&fd1, sizeof(fd1), 1, fptr); 
			//printf("%ld",fd1.llocation_block_no);
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
	fptr = fopen(name, "rb+"); // opening file for read/write
	if(fptr == NULL) {
		printf("\nError in Mounting VFS\n");
	}
	
	else {
		fseek(fptr,0,SEEK_SET);
		fread(&m1, sizeof(m1), 1, fptr);
		//printf("\n--------------------Initializing Bitmap\n");
		bitMapInit();
		initialzeHashTable(&ht1);
		//printf("\n--------------------Bitmap Initialized\n");
		//printf("\n--------------------VFS Mounting\n");
		//printf("\n--------------------VFS Mounted\n");
		
		//initialize data structure
		//printf("\n--------------------Initializing Data Structures\n");
		fseek(fptr,m1.freedescriptor,SEEK_SET);
		int k = 1;
		for (; k<= m1.ltotal_file_descriptors; k++) {
			fread(&fd1, sizeof(fd1), 1, fptr);
			//printf("outside %ld",fd1.llocation_block_no);
			if(fd1.llocation_block_no != -9999) { 
				//printf("inside %ld\n",fd1.llocation_block_no);
				//printf("%s\n",fd1.sfile_name);
				//call n-aray insert function
				insert_node(&root, &fd1);
				//printf("%d", rs);
				//call hash table insert function
				insertHashTable(&ht1, &fd1);
				//call BST insert function
				insertBst(&fd1);
				//List_Node *start = searchHashTable(&ht1, "abc");
				//if(start == NULL) {
					//printf("file not found\n");
				//}
				//else {
					//printf("found\n"); 
					//search_File("abc", "abc");
				//}
			
			}
		}
		//displayList();
		//printtree(&root);
		//ln1 = (List_Node*)malloc(sizeof(List_Node*));
		

	}
}

void unmount_VFS() {
	//printf("\n--------------------Unmounting VFS\n");
	fclose(fptr);
	free(fl1.bitmap);
	//printf("\n--------------------VFS Unmounted\n");
}	

int search_File(char *name, char *outputfile) {
	List_Node *start = searchHashTable(&ht1, name);
				if(start == NULL) {
					printf("file not found\n");
				}
				else {
					FILE *ft = fopen (outputfile, "a+" ) ;
					if ( ft == NULL )
							{
								perror ("cannot open file") ;
								fclose ( ft ) ;
								return 0;
							}
					else {
						while(start != NULL) {
							//printf("%s\t%s\n", start->data->sfile_name, start->data->slocation_full_path);
							fprintf(ft, "%s\t%s\n", start->data->sfile_name, start->data->slocation_full_path) ;
							//fputs(start->data->slocation_full_path, ft) ;
						start=start->next;
						}
					}
					fclose ( ft ) ;
				}
				return 1;
}

void make_Dir(char *parentpath, char *dirname) {
	//printf("%s %s", parentpath, dirname);
	int flag;
	fseek(fptr,m1.freeblock,SEEK_SET);
	//printf("after seek");
	//getting the first free location from the Bitmap
	long a = freeLocation();
	fseek(fptr,a*sizeof(b1),SEEK_CUR);
	//fwrite(&arr, sizeof(arr), 1, fptr);
	
	//Sending pointer to write at the free location of the File Descriptor
	fseek(fptr,m1.freedescriptor,SEEK_SET);
	fseek(fptr,a*sizeof(fd1),SEEK_CUR);
	strcpy(fd1.sfile_name, dirname);
	strcpy(fd1.slocation_full_path, parentpath);
	fd1.sfile_type = 'd';
	fd1.lfile_size = 0;
	fd1.llocation_block_no = a;
	fwrite(&fd1, sizeof(fd1), 1, fptr);
	//Update bit map by passing block no. of occupied block
	bitmapUpdate(a, 1);
	flag = insert_node(&root, &fd1);
	if(flag == 0) {
	printf("SUCCESS\n");
	}
	else {
	printf("FAIL");
	}
	printtree(&root);
	
}

void write_File() {
	
	char file_name[100];  
	char path[512];
	char ch,arr[1024];
	
	fseek(fptr,m1.freeblock,SEEK_SET);
	//printf("after seek");
	//getting the first free location from the Bitmap
	long a = freeLocation();
	
	
	fseek(fptr,a*sizeof(b1),SEEK_CUR);

	//Write files to the file system
		printf("Enter the Name of file: \n");
		scanf("%s", file_name);
		printf("Enter the path of file: \n");
		scanf("%s", path);
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
	
	//Sending pointer to write at the first location of the FDescript
	fseek(fptr,m1.freedescriptor,SEEK_SET);
	fseek(fptr,a*sizeof(fd1),SEEK_CUR);
	strcpy(fd1.sfile_name, file_name);
	strcpy(fd1.slocation_full_path, path);
	fd1.sfile_type = 'f';
	//fd1.sfile_type;
	fd1.lfile_size = sizeof(arr);
	fd1.llocation_block_no = a;
	fwrite(&fd1, sizeof(fd1), 1, fptr);
	//Update bit map by passing block no. of occupied block
	bitmapUpdate(a, 1);
}

int add_File(char* dest, char* fname, char* src) {
	char ch,arr[1024];
	int c;
	fseek(fptr,m1.freeblock,SEEK_SET);
	//printf("after seek");
	//getting the first free location from the Bitmap
	long a = freeLocation();
	
	fseek(fptr,a*sizeof(b1),SEEK_CUR);
    FILE *fp ;
         fp = fopen(src,"r") ;
         //printf("here %s", src);
         if( fp == NULL )
         {
               perror ("cannot open file") ;
               return 0;
         }
         else{
			int i=0;
			while (fgetc(fp) != EOF) {
				ch = fgetc ( fp );
				arr[i] = ch;
				i++;
			}
			fclose(fp);
			//printf("\n%s\n", arr);
		 }

	//Write files to the file system
	//printf("before write");
	fwrite(&arr, sizeof(arr), 1, fptr);
	
	//Sending pointer to write at the first location of the FDescriptor
	fseek(fptr,m1.freedescriptor,SEEK_SET);
	fseek(fptr,a*sizeof(fd1),SEEK_CUR);
	strcpy(fd1.sfile_name, fname);
	strcpy(fd1.slocation_full_path, dest);
	//fd1.sfile_type;
	fd1.lfile_size = sizeof(arr);
	fd1.llocation_block_no = a;
	fd1.sfile_type = 'f';
	fwrite(&fd1, sizeof(fd1), 1, fptr);
	//Update bit map by passing block no. of occupied block
	bitmapUpdate(a, 1);
	//inserting into naray
	insert_node(&root, &fd1);
	//inserting into hashtable
	insertHashTable(&ht1, &fd1);
	//inserting into BST
	insertBst(&fd1);
	return 1;
}

void delete_File() {

}

/*writing code for bit map.*/
//Initializing bitmap to zero
void bitMapInit() {
	long totalfiledescs = m1.ltotal_file_descriptors;
	fl1.bitmap = (char*)malloc(m1.ltotal_file_descriptors * sizeof(char));
	long i;
	fseek(fptr,m1.freedescriptor,SEEK_SET);
	for(i=0;i < totalfiledescs; i++){
		//fseek(fptr,i*sizeof(fd1),SEEK_CUR);
		fread(&fd1, sizeof(fd1), 1, fptr);
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
	if (flag ==1 ) // occupied
	fl1.bitmap[n]=1;	
	else //empty
	fl1.bitmap[n]=0;		
}

void stats()
{

		printf("\nMount Label: %s", m1.sfile_system_label);
		printf("\nNext Free File Descriptor Location :%ld", m1.freedescriptor + sizeof(fd1) * (freeLocation()));
		printf("\nNext Free Block Location: %ld", m1.freeblock + sizeof(b1) * (freeLocation()));
		//printf("\nNext Free Block Location: %ld", m1.freeblock);
		printf("\nTotal File Blocks: %ld", m1.ltotal_file_blocks);
		printf("\nAvailable File Blocks: %ld", m1.ltotal_file_blocks - freeLocation());
		printf("\nTotal File Descriptors: %ld", m1.ltotal_file_descriptors);
		printf("\nAvailable File Descriptors: %ld\n", m1.ltotal_file_descriptors - freeLocation());
		//fclose(fptr);
}
