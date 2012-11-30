#include <stdio.h>
#include "../include/vfs_17.h"
#include "../include/bst.h"
#include "../include/hashtable.h"
#include "../include/linkedlist.h"
#include "../include/nary.h"
#include "../include/vfs_errorcodes.h"
#include <string.h>
#include <stdlib.h>
//#include <sys/statvfs.h>

//global variables
struct Main_Header m1; 
struct Block b1;
struct File_Descriptor fd1;
struct Free_List fl1;
struct Hash_Table ht1;
struct List_Node *ln1;
static int MOUNTED = 0;
//struct node *bstRoot = NULL;
t_node *root = NULL;
FILE *fptr; // pointer to the file object	

//special functions
int textfilecheck(char *);
int fileformatcheck(char*, char*);
//int disccheck(long);

int search_File(char*, char*);
int list_File(char*, char*);

	
/*int disccheck(long size) {
	struct statvfs fiData;
	struct statvfs *fpData;
	char fnPath[128];
	int i;
	//Lets loopyloop through the argvs

	strcpy(fnPath,"/");
	// printf("Disk %s: \n", fnPath);
	//printf("\tblock size: %lu\n", fiData.f_bsize);
	//printf("\ttotal no blocks: %d\n", fiData.f_blocks);
	//printf("\tfree blocks: %lu\n", fiData.f_bfree);
	double total = (double)fiData.f_bsize * (double)fiData.f_bfree;
	//printf("%lf\n",total);
	if(total <= (double)size)
	{return 0;}
return 1;
}
*/
/* function for creating the large binary file for VFS */
int create_VFS(char *vfsname, long size) {

	//mounted so no more vfs
	if(MOUNTED == 1){ return 02; }

	//insufficient arguments
	if(size == -1) { return 00; }
	
	long mysize = ((size + 5) * 1024) + sizeof(m1) + sizeof(fd1);
	
	//insufficient arguments
	if(strcmp(vfsname, "") == 0) { return 00; }

	
	
	//check for name validity
	if(strstr(vfsname, "/") != NULL) { return 04; }
	
	//check for vfs label too large
	if(strlen(vfsname) > 30) { return 07; }
	
	long reqsize = sizeof(m1)+sizeof(b1)+sizeof(fd1);
	/*checking for enough memory*/
	//int dchk = disccheck(reqsize);
	//if(dchk == 0) { return 3; } 
	
	/*checking for minimum size*/
	if(mysize < reqsize || size < 1 || size > 1024) {
		return 05;
	}
	
	//checking for datafile already exist
	fptr = fopen(vfsname, "rb");
	if(fptr != NULL) {
		fclose(fptr);
		return 01;
	}
	
	
	int i=1, j=1; //loop variable for creating file descritors and file blocks
	
	//printf("--------------------Creating VFS-----------------------------");
	
	strcpy(m1.sfile_system_label, vfsname);  //storing the VFS label
	//printf("\nvfs name : %s", m1.sfile_system_label);
	//printf("\nsize of meta header: %ld", sizeof(m1));
	m1.lsize = mysize - sizeof(m1); // size remaining after creation of meta header 
	
	//printf("\nsize left after ceation of meta header: %ld", m1.lsize);
	m1.ltotal_file_descriptors = (m1.lsize)/(sizeof(fd1) + sizeof(b1)); // calculating the no. of file descriptors can be used in remaining space
	
	//printf("\nsize of each file descriptor : %ld", sizeof(fd1));
	//printf("\ntotal file descriptors : %ld", m1.ltotal_file_descriptors);
    m1.lsize = m1.lsize - (m1.ltotal_file_descriptors * sizeof(fd1)); // size remaining after creation of file descriptors
    
    //printf("\nsize left after creation of file descriptors: %ld", m1.lsize);
    m1.ltotal_file_blocks = (m1.lsize)/(sizeof(b1)); // calculating the no. of file blocks can be used in remaining space
    
  
    //printf("\nsize of each file block : %ld", sizeof(b1));
    //printf("\ntotal file blocks : %ld", m1.ltotal_file_blocks);
    m1.lsize = m1.lsize - (m1.ltotal_file_blocks * sizeof(b1)); // calculating the space unused 
	
	//printf("\nspace unsed: %ld\n", m1.lsize);
    
     
		
    /* wrting the large binary file of given size including- 
     * 1.meta header
     * 2.file descriptors and
     * 3.file blocks
     */
     
	
	
	fptr = fopen(vfsname, "wb"); // opening the file with given label in binary write mode
	if(fptr == NULL) {
		return 02; // cannot create datafile
	}
	else {
		//long first_loc_fblock = ftell(fptr);
		m1.freedescriptor = 1 + (sizeof(m1));
		m1.freeblock = 1 + (m1.freedescriptor  + m1.ltotal_file_descriptors*sizeof(fd1));   
		//printf("\n%ld", m1.freedescriptor);
		//printf("\n%ld", m1.freeblock);
		// writing meta header
		fwrite(&m1, sizeof(m1), 1, fptr); 
		//printf("\nmeta header created\n");
	    
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
		//printf("file  descriptor created\n"); 
	    // writing file blocks
	    for (; j<= m1.ltotal_file_blocks; j++) {
			fwrite(&b1, sizeof(b1), 1, fptr); 
		}
		//printf("file block created\n"); 
		fclose(fptr); // closing the file to store it in persistent memory
		//printf("\n--------------------VFS Created-----------------------------\n");
	}
	return 10;
}

//mounting vfs
int mount_VFS(char *mname) {
	
	
	//vfs already mounted
	if(MOUNTED == 1){ return 04; }

	//insufficient arguments
	if(strcmp(mname, "") == 0) { return 00; }
	
	
	fptr = fopen(mname, "rb+"); // opening file for read/write
	if(fptr == NULL) {
		return 01; //datafile not found
	}

	else {
		//reading the meta header
		fseek(fptr,0,SEEK_SET);
		
		//checking for CANNOT READ FROM FILE"
		int checkm = fread(&m1, sizeof(m1), 1, fptr);
		if( checkm == 0) {
			return 02;
		} 
		else {
		//
		//initializing bitmap
		bitMapInit();
		//initializing hashtable 
		initialzeHashTable(&ht1);
		root = nary_insert_root();
		//reading file descriptors
		fseek(fptr,m1.freedescriptor,SEEK_SET);
		int k = 1;
		for (; k<= m1.ltotal_file_descriptors; k++) {
			fread(&fd1, sizeof(fd1), 1, fptr);
			if(fd1.llocation_block_no != -9999) { 
				//inserting into naray
				insert_node(&fd1,root);
				//call hash table insert function
				//if (fd1.sfile_type == 'f')
				//{
					//printf("%s\n", fd1.sfile_name );
					insertHashTable(&ht1, &fd1);
				//}
				//call BST insert function
				insertBst(&fd1);
			}
		}
	}
	MOUNTED = 1;
	}
	//printf("vfs name: %s", m1.sfile_system_label);
	//strcpy(VFS_NAME, m1.sfile_system_label);
	return 10;
}

int make_dir(char *parent_path, char *dir_name){
	//printf("******************in make dir****************");
	//displayList();
	//printf("%s %s", parent_path, dir_name);
	char parent_pathpure[512] = "";

	//vfs not mounted
	if(MOUNTED == 0){ return 05; }

	if(strcmp(parent_path, "") == 0) { return 00; }
	if(strcmp(dir_name, "") == 0) { return 00; }
	
	
	int fss = freeLocation();	
	if (fss == -1) {
	return 01;
	}
	
	//check for name validity
	if(strstr(dir_name, "/") != NULL) { return 02; }

	if(strcmp(parent_path,"/")!=0) {
		if(parent_path[strlen(parent_path)- 1] == '/') {
			//printf("Here\n");
			strncpy(parent_pathpure, parent_path, strlen(parent_path) - 1);
		}
		else{strcpy(parent_pathpure, parent_path);}
	}
	else{strcpy(parent_pathpure, parent_path);}
	
	char totalPath[512];
	 if(strcmp(parent_path,"/")!=0)
        {
			strcpy(totalPath,parent_pathpure);
			strcat(totalPath,"/");
			strcat(totalPath,dir_name);
        }
        else
        {
            strcpy(totalPath,"/");
            strcat(totalPath,dir_name);
        }
	//printf("dir_name : %s parent_path : %s",dir_name,parent_path);
	char *token[80]; 
	int exist = searchBst(totalPath);
	//struct node* t = searchBstFD(parent_path);
	//if(t!=NULL)
	//printf("/n************no null**********/n" );
	//else
	//printf("/n************null**********/n" );
	if(exist!=1){
		int existParentPath = searchBst(parent_pathpure);
		//printf("existParentPath %d",existParentPath);
		if(!existParentPath){
			int j, i=0; 
			char parent_path_temp[512];
			strcpy(parent_path_temp,parent_pathpure);
			token[0] = strtok(parent_path_temp, "/"); 
			while(token[i]!= NULL) { 
   
			//	printf("%s\n", token[i]); 
				i++;
				token[i] = strtok(NULL, "/"); 
			}

			char subPath[512];
			char prevPath[512];
			strcpy(subPath,"/");
			for(j = 0; j <= i-1; j++) {
				strcpy(prevPath,subPath);
				if(strcmp(prevPath,"/")!=0)
				{
					strcpy(subPath,prevPath);
					strcat(subPath,"/");
					strcat(subPath,token[j]);
				}
				else
				{
					strcpy(subPath,"/");
					strcat(subPath,token[j]);
				}
				
				int existParent = searchBst(subPath);
				if(!existParent){
					dirInsert(prevPath,token[j]);
				}
			
			}
		}
		//if(token[0]==""){
			dirInsert(parent_pathpure, dir_name);
			
			
			//printf("BST Diplay\n \n");
			//displayList();
			//printf("narray Diplay\n \n");
			//printtree(root);
			//printf("narray Diplay ends\n \n");
		//}
	} else { return 03; }

return 10;
}

int move_dir(char* source_path,char* destination_path){
	
	char source_pathtmp[512] = "";
	char destination_pathtmp[512] = "";
	//insufficient argument

	//not munted
	if(MOUNTED == 0){ return 04; }

	if(strcmp(source_path, "") == 0) { return 00; }
	if(strcmp(destination_path, "") == 0) { return 00; }


	if(strcmp(source_path,"/")!=0) {
		if(source_path[strlen(source_path)- 1] == '/') {
			//printf("Here\n");
			strncpy(source_pathtmp, source_path, strlen(source_path) - 1);
		}
		else{strcpy(source_pathtmp, source_path);}
	}
	else{strcpy(source_pathtmp, source_path);}

	if(strcmp(destination_path,"/")!=0) {
		if(destination_path[strlen(destination_path)- 1] == '/') {
			//printf("Here\n");
			strncpy(destination_pathtmp, destination_path, strlen(destination_path) - 1);
		}
		else{strcpy(destination_pathtmp, destination_path);}
	}
	else{strcpy(source_pathtmp, source_path);}

	struct node *ndsrc4 = searchBstFD(source_pathtmp);
	struct node *nddest4 = searchBstFD(destination_pathtmp);
	
	//source not found
	if(ndsrc4 == NULL) { return 01;}

	//dest not found
	if(nddest4 == NULL) { return 02;}

	//source is not file
	if( ndsrc4->fd1->sfile_type == 'f') { return 04; }

	//dest is not file
	if( nddest4->fd1->sfile_type == 'f') { return 07; }

	//printf("in move dir\n");
	//move_node(root,source_pathtmp,destination_pathtmp);

return 10;
}
int dirInsert(char *parent_path, char *dir_name){
	
			//fseek(fptr,m1.freeblock,SEEK_SET);
			//printf("dir name in dir insert is %s and parent_path is %s\n", dir_name,parent_path);
			//getting the first free location from the Bitmap
			long a = freeLocation();
			
			/*struct File_Descriptor *fd = (struct File_Descriptor*)malloc(sizeof(struct File_Descriptor));
			strcpy(fd->sfile_name, dir_name);
			strcpy(fd->slocation_full_path, parent_path);
			fd->sfile_type = 'd';
			fd->lfile_size = 0;
			fd->llocation_block_no = a;*/
			
			//Sending pointer to write at the first location of the FDescriptor
	fseek(fptr,m1.freedescriptor,SEEK_SET);
	fseek(fptr,a*sizeof(fd1),SEEK_CUR);
	strcpy(fd1.sfile_name, dir_name);
	strcpy(fd1.slocation_full_path, parent_path);
	//fd1.sfile_type;
	fd1.lfile_size = 0;
	fd1.llocation_block_no = a;
	fd1.sfile_type = 'd';
	fwrite(&fd1, sizeof(fd1), 1, fptr);
	
			//fwrite(&fd1, sizeof(fd1), 1, fptr);
			//Update bit map by passing block no. of occupied block
			bitmapUpdate(a, 1);
			t_node *flag = insert_node(&fd1,root);
			//inserting into hashtable
			//insertHashTable(&ht1, fd);

			//inserting into BST
			insertBst(&fd1);
			//inserting into hashtable
			insertHashTable(&ht1, &fd1);
			if(flag !=NULL) {
			//printf("SUCCESS\n");
			}
			else {
			//printf("FAIL");
			}
return 10;	
}

int list_dir(char* path,int flag,char *harddiskpath) {
	//char path[100] = "";
	//printf("%s\n", harddiskpath);	
	//not munted
	if(MOUNTED == 0){ return 03; }
	//insufficient arguments
	if(strcmp(path, "") == 0) { return 00; }
	if(flag == -1) { return 00; }
	if(strcmp(harddiskpath, "") == 0) { return 00; }
	
	// Invalid flag
	if(flag !=0 && flag !=1) {return 02;}

	/*if(strcmp(pathtmp,"/")!=0) {
		if(pathtmp[strlen(pathtmp)- 1] == '/') {
			//printf("Here\n");
			strncpy(path, pathtmp, strlen(pathtmp) - 2);
		}
	}*/
	
	int errcode = list_tree(&root,flag,path,harddiskpath);
	return errcode;
}

int delete_dir(char *path) {
	//printf("above");
	//insufficient arguments
	char purepath[512] = "";

	//not munted
	if(MOUNTED == 0){ return 04; }

	if(strcmp(path, "") == 0) { return 00; }


	if(strcmp(path,"/")!=0) {
		if(path[strlen(path)- 1] == '/') {
			//printf("Here\n");
			strncpy(purepath, path, strlen(path) - 1);
		}
		else{
			strcpy(purepath, path);
		}
	}

	struct node *nd = searchBstFD(purepath);
	if (nd != NULL) {
	//printf("in dele dir b4 dele \n");
	//printtree(root);
	int deli = delete(nd->fd1,root);
	if(deli == 2) { return 02;} 
	//printf("in dele dir after dele nary \n");
	//printtree(root);
	//deleting from BSTl
	//deleteBstElm(filepath);
	//deleting from Hash Table
	//deleteHashTable(&ht1, nd->fd1->sfile_name);
	//detele from naray yet to be done
	//making bitmap available
	//long a= nd->fd1->llocation_block_no;
	//bitmapUpdate(a, 0);
}
else {
return 01;
}
return 10;
}

int unmount_VFS(char *uname) {
	if(MOUNTED == 0){ return 04; }

	//insufficient arguments
	if(strcmp(uname, "") == 0) { return 0; }
	//printf("uname: %s vfslabel: %s\n", uname, m1.sfile_system_label);

	if(strcmp(m1.sfile_system_label, uname) == 0){
		//printf("\n--------------------Unmounting VFS\n");
		fclose(fptr);
		free(fl1.bitmap);
		//printf("\n--------------------VFS Unmounted\n");
		MOUNTED = 0;
		return 10;
	}
	else { return 04; }
}	


//file format check
int fileformatcheck(char *path, char *modpath){
char *string;
char *strtmpsrc;
string = path;
char *tokenPtr;
tokenPtr = strtok( string, "." );
tokenPtr = (strtmpsrc = strtok( NULL, "." )) ? strtmpsrc : "";

char *string2;
char *strtmp;
string2 = modpath;
char *tokenPtr2;
tokenPtr2 = strtok( string2, "." );
tokenPtr2 = (strtmp = strtok( NULL, "." ))? strtmp : "";

if(strcmp(tokenPtr, tokenPtr2) == 0)
{return 1;}
else{return 0;}
}

//update edit file
int update_File(char *filepath, char *src) {

	//vfs not mounted
	if(MOUNTED == 0){ return 06; }

	//insufficient arguments
	if(strcmp(filepath, "") == 0) { return 00; }
	//insufficient arguments
	if(strcmp(src, "") == 0) { return 00; }
	
	
	

	char ch,arr[1024] = "";
	struct node *nd = searchBstFD(filepath);
	FILE *fp ;
		fp = fopen(src,"rb") ;
	
	//file format check
	if(fileformatcheck(filepath, src) == 0) { return 05; }
	
	
	if (nd != NULL) {
		//erase previous data
		fseek(fptr,m1.freeblock,SEEK_SET);
		long a= nd->fd1->llocation_block_no;
		fseek(fptr,a*sizeof(b1),SEEK_CUR);
		fwrite(&arr, sizeof(arr), 1, fptr);
		
		//write new data
		fseek(fptr,m1.freeblock,SEEK_SET);
		fseek(fptr,a*sizeof(b1),SEEK_CUR);
		
        
         if( fp == NULL )
         {
			  //printf("here %s", src);
               return 01; //source file not found
         }
         else {
			  //printf("hereddd %s", src);
				//file size check
				fseek(fp, 0L, SEEK_END);
				long sz = ftell(fp);
				if(sz > sizeof(b1)) { return 04; } //file too large
				//file size check
			  
				fseek(fp, 0L, SEEK_SET);
				fread(&arr, sizeof(arr), 1, fp);
				fclose(fp);
				//printf("\n%s\n", arr);
		 }

	//Write files to the file system
	fwrite(&arr, sizeof(arr), 1, fptr);
	//Sending pointer to write at the first location of the FDescriptor
	
	//read old file descriptor
	fseek(fptr,m1.freedescriptor,SEEK_SET);
	fseek(fptr,a*sizeof(fd1),SEEK_CUR);
	struct File_Descriptor fdtemp;
	fread(&fdtemp, sizeof(fdtemp), 1, fptr);
	
	//write updated file descriptor
	fseek(fptr,m1.freedescriptor,SEEK_SET);
	fseek(fptr,a*sizeof(fd1),SEEK_CUR);
	strcpy(fd1.sfile_name, fdtemp.sfile_name);
	strcpy(fd1.slocation_full_path, fdtemp.slocation_full_path);
	
	fd1.lfile_size = sizeof(arr);
	fd1.llocation_block_no = a;
	fd1.sfile_type = 'f';
	fwrite(&fd1, sizeof(fd1), 1, fptr);
	}
	else {
		return 02; //destination file not found
	}
return 10;					
}

int textfilecheck(char *path){
char *string;
string = path;
char *strtmpsrc;
char *tokenPtr;
tokenPtr = strtok( string, "." );
tokenPtr = (strtmpsrc = strtok( NULL, "." )) ? strtmpsrc : "";
if(!strcmp(tokenPtr,"txt"))
{return 1;}
else{return 0;}
}

//list file function
int list_File(char *filepath, char *harddiskpath) {
	
	//vfs not mounted
	if(MOUNTED == 0){ return 06; }

	//insufficient arguments
	if(strcmp(filepath, "") == 0) { return 00; }
	//insufficient arguments
	if(strcmp(harddiskpath, "") == 0) { return 00; }
	
	
	//not a text file
	struct node *nd = searchBstFD(filepath);
	if(!textfilecheck(filepath)) {
		return 05;
	}
	else {
	if (nd != NULL) {
		fseek(fptr,m1.freeblock,SEEK_SET);
		long a = nd->fd1->llocation_block_no;
		fseek(fptr,a*sizeof(b1),SEEK_CUR);

		//strcat(harddiskpath, "/");
		//strcat(harddiskpath, nd->fd1->sfile_name);
		
		FILE *fp = fopen (harddiskpath, "wt+" ) ;
					if ( fp == NULL )
							{
								//perror ("cannot open file") ;
								return 02; //output file path not found
					}
					else {
						fread(&b1, sizeof(b1), 1, fptr);
						int i=0;
						while(b1.sfixed_size_buffer[i] != '\0') {
							fputc(b1.sfixed_size_buffer[i], fp);
							i++;
						}
					}
						fclose(fp);
	}
			else {
				//printf("path not found\n");
				return 01; // source file path not found
			}		
	}
	return 10;			
}

//remove file function
int remove_File(char *filepath) {

	//vfs not mounted
	if(MOUNTED == 0){ return 06; }

	//insufficient arguments
	if(strcmp(filepath, "") == 0) { return 00; }
	
	
	struct node *nd = searchBstFD(filepath);
	if (nd != NULL) {
		//deleting from BST
		deleteBstElm(filepath);
		//deleting from Hash Table
		deleteHashTable(&ht1, nd->fd1->sfile_name, nd->fd1->slocation_full_path);
		//detele from naray
		delete_dir(filepath);
		//making bitmap available
		long a= nd->fd1->llocation_block_no;
		bitmapUpdate(a, 0);
	}
	else {
		return 01;
	}	
return 10;			
}

//export_file function
int export_File(char *filepath, char *outputfile) {
	//printf("above");

		//vfs not mounted
	if(MOUNTED == 0){ return 07; }

	//source path missing
	if(strcmp(filepath, "") == 0) { return 00; }
	//destination path missing
	if(strcmp(outputfile, "") == 0) { return 00; }
	
	
	struct node *nd = searchBstFD(filepath);
	if (nd != NULL) {
		//can not export directory
		if( nd->fd1->sfile_type == 'd') { return 06; }
		fseek(fptr,m1.freeblock,SEEK_SET);
		long a= nd->fd1->llocation_block_no;
		//printf("%ld\n", a);
		
		//strcat(outputfile, "/");
		//strcat(outputfile, nd->fd1->sfile_name);
		
		/*FILE *fptre = fopen(outputfile, "rb");
		if(fptre != NULL) {
			return 05;
		}*/
		
		fseek(fptr,a*sizeof(b1),SEEK_CUR);
		FILE *fp = fopen (outputfile, "wb+" ) ;
					if ( fp == NULL )
							{
								//printf("here");
								return 02;
					}
					else {
						fread(&b1, sizeof(b1), 1, fptr);
						int i=0;
						while(b1.sfixed_size_buffer[i] != '\0') {
							fputc(b1.sfixed_size_buffer[i], fp);
							i++;
							}
						
					}
						fclose(fp);
	}
	else {
		return 01;
	}	
return 10;					
}
//move file
int move_File(char *srcfilepath, char *destfilepathtmp) {

	//vfs not mounted
	if(MOUNTED == 0){ return 06; }
	
	char destfilepath[200] = "";
	//insufficient arguments
	if(strcmp(srcfilepath, "") == 0) { return 00; }
	//insufficient arguments
	if(strcmp(destfilepathtmp, "") == 0) { return 00; }
	

	if(strcmp(destfilepathtmp,"/")!=0) {
		if(destfilepathtmp[strlen(destfilepathtmp)- 1] == '/') {
			//printf("Here\n");
			strncpy(destfilepath, destfilepathtmp, strlen(destfilepathtmp) - 1);
		}
		else {
			strcpy(destfilepath, destfilepathtmp);
		}
	}else {
			strcpy(destfilepath, destfilepathtmp);
		}
	
	//source file exists or not
	struct node *ndsrc1 = searchBstFD(srcfilepath);
	if( ndsrc1 == NULL) { return 01; }
	
	//dest path exists or not
	struct node *ndsrc2 = searchBstFD(destfilepath);
	if( ndsrc2 == NULL) { return 02; }
	
	//dest is not a file
	struct node *ndsrc3 = searchBstFD(destfilepath);
	if( ndsrc3->fd1->sfile_type == 'f') { return 05; }
	
	//source is not dir
	struct node *ndsrc4 = searchBstFD(srcfilepath);
	if( ndsrc4->fd1->sfile_type == 'd') { return 01; }
	
	
	copy_File(srcfilepath,  destfilepath);
	remove_File(srcfilepath);
	//printlist(ln1);
	//displayList();
	return 10;
	
}
//copy file
int copy_File(char *srcpath, char *destpath) {
	
	//vfs not mounted
	if(MOUNTED == 0){ return 07; }

	//source path missing
	if(strcmp(srcpath, "") == 0) { return 00; }
	//destination path missing
	if(strcmp(destpath, "") == 0) { return 00; }
	

	int fss = freeLocation();	
	if (fss == -1) {
	return 06;
	}
	
	char temparr[1024];
	char full_path[100] = "";
	//checking
	
	struct node *ndsrc = searchBstFD(srcpath);
	
	if (ndsrc != NULL) {
		if( ndsrc->fd1->sfile_type == 'd') { return 05; }
		fseek(fptr,m1.freeblock,SEEK_SET);
		long a = ndsrc->fd1->llocation_block_no;
		fseek(fptr,a*sizeof(b1),SEEK_CUR);
		fread(&b1, sizeof(b1), 1, fptr);
						int i=0;
						while(b1.sfixed_size_buffer[i] != '\0') {
							temparr[i] = b1.sfixed_size_buffer[i]; 
							i++;
							}
		}
	else {	
		return 01;				
	}
		//printf("%ld\n", a);
		
						
						int tmp;
						if(strcmp(destpath,"/")!=0) {
							//strcpy(full_path,destpath);
							/*if(full_path[strlen(full_path-1)] !='/') {
								strcat(full_path,"/");
							}*/
							if(destpath[strlen(destpath) - 1] == '/') {
								//printf("Here\n");
								strncpy(full_path, destpath, strlen(destpath) - 1);
								//dest[strlen(dest - 1)] = '\0';
								//printf("%s\n",dest);
							}
							else{
								strcpy(full_path, destpath);
							}


							//strcat(full_path,ndsrc->fd1->sfile_name); */
						}
						/*else {
							if(full_path[strlen(full_path-1)] !='/') {
								strcat(full_path,"/");
							}
							//strcat(full_path,ndsrc->fd1->sfile_name);
						}*/
						tmp = searchBst(full_path);
						if (tmp == 0) { 
						return 02; //cant find dest path
						}
						
						fseek(fptr, m1.freeblock,SEEK_SET);
						//printf("after seek");
						//getting the first free location from the Bitmap
						long b = freeLocation();
						fseek(fptr,b*sizeof(b1),SEEK_CUR);
						//Write files to the file system
	//printf("before write");
	fwrite(&temparr, sizeof(temparr), 1, fptr);
	
	//Sending pointer to write at the first location of the FDescriptor
	fseek(fptr,m1.freedescriptor,SEEK_SET);
	fseek(fptr,b*sizeof(fd1),SEEK_CUR);
	strcpy(fd1.sfile_name, ndsrc->fd1->sfile_name);
	strcpy(fd1.slocation_full_path, full_path);
	//fd1.sfile_type;
	fd1.lfile_size = sizeof(temparr);
	fd1.llocation_block_no = b;
	fd1.sfile_type = 'f';
	
	fwrite(&fd1, sizeof(fd1), 1, fptr);
	//printf("%ld", fd1.llocation_block_no);
	//Update bit map by passing block no. of occupied block
	bitmapUpdate(b, 1);
	//inserting into naray
	insert_node(&fd1,root);
	//inserting into hashtable
	insertHashTable(&ht1, &fd1);
	//inserting into BST
	insertBst(&fd1);
	//return 1;
return 10;		
}

//file search function
int search_File(char *sname, char *outputfile) {
	//printlist(ln1);
	//creating list of file
	//output path missing
	//printf("%s\n",sname);
		//vfs not mounted
	if(MOUNTED == 0){ return 03; }

	if(strcmp(outputfile, "") == 0) { return 00; }

	if(strstr(sname, "/") != NULL) { return 02; }

	//printf("vfslabel: %s\n", m1.sfile_system_label);
	
	List_Node *start = searchHashTable(&ht1, sname);
				if(start == NULL) {
					return 04;
				}
				else {
					FILE *ft = fopen (outputfile, "w+" ) ;
					if ( ft == NULL )
							{
								return 01; //cannot find specified output file
							}
					else {
						while(start != NULL) {
							fprintf(ft, "%s\t%s\n", start->data->sfile_name, start->data->slocation_full_path) ;
							start=start->next;
						}
					}
					fclose ( ft ) ;
				}
return 10;
}


int add_File(char* dest, char* fname, char* src) {
	

		//vfs not mounted
	if(MOUNTED == 0){ return 07; }
	//printf("%s\n",dest);
	
	//insufficient arguments
	char destpurified[512] = "";
	if(strcmp(dest, "") == 0) { return 00; }
	//insufficient arguments
	if(strcmp(fname, "") == 0) { return 00; }
	//insufficient arguments
	if(strcmp(src, "") == 0) { return 00; }


	
	//check for name validity
	if(strstr(fname, "/") != NULL) { return 02; }

	//printf("%s\n",dest);
	//printf("%d\n",strlen(dest) - 1);
	//purify argument
	//char desttmp[100] = "";
	if(strcmp(dest,"/")!=0) {	
		if(dest[strlen(dest) - 1] == '/') {
				//printf("Here\n");
				strncpy(destpurified, dest, strlen(dest) - 1);
				//dest[strlen(dest - 1)] = '\0';
				//printf("%s\n",destpurified);
		}
		else {
			strcpy(destpurified, dest);
		}
	}
	//printf("Here 1 \n");
	char basefolder[512] = "";
	char basename[80] = "";
	//printf("%s\n", destpurified);
	//create directory if not exists
	if(strcmp(dest,"/")!=0) {

		struct node *nddest = searchBstFD(destpurified);
		if(nddest == NULL) { 
			
			strcpy(basename, strrchr(destpurified, '/') + 1);
			//printf("before\n");
			//printf("basename %s\n", basename);
			strncpy(basefolder, destpurified, strlen(destpurified) - strlen(basename) - 1);
			//printf("basefolder %s\n", basefolder);
			make_dir(basefolder, basename);
		}
	}
	//printf("after\n");
	//printtree(root);

	//checking for file system space
	int fss = freeLocation();	
	if (fss == -1) {
	return 01;
	}
	else {
	//checking for file existence
	char full_path[512];
	int tmp;
	if(strcmp(dest,"/")!=0)
        {
            strcpy(full_path,dest);
            if(dest[strlen(dest) - 1] != '/') {

            	strcat(full_path,"/");
        	}
            strcat(full_path,fname);
        }
        else
        {
            strcat(full_path,"/");
            strcat(full_path,fname);
        }
	tmp = searchBst(full_path);
	if (tmp == 1) { 
		return 3; //file already exists
	} 
	
	char ch,arr[1024];
	int c;
	fseek(fptr,m1.freeblock,SEEK_SET);
	//printf("after seek");
	//getting the first free location from the Bitmap
	long a = freeLocation();
	
	fseek(fptr,a*sizeof(b1),SEEK_CUR);
    FILE *fp ;
         fp = fopen(src,"rb") ;
         //printf("here %s", src);
         if( fp == NULL )
         {
               //perror ("cannot open file") ;
               return 05; //can not open specified data file
         }
         else{
			 
			//file size check
			fseek(fp, 0L, SEEK_END);
			long sz = ftell(fp);
			if(sz > sizeof(b1)) { return 06; } //file too large
			//file size check
			 
			fseek(fp, 0L, SEEK_SET);
			int i;
			for(i=0;i<1024;i++)
			{
					arr[i]='\0';
			}
			fread(&arr, sizeof(arr), 1, fp);
			
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
	strcpy(fd1.slocation_full_path, destpurified);
	//fd1.sfile_type;
	fd1.lfile_size = sizeof(arr);
	fd1.llocation_block_no = a;
	fd1.sfile_type = 'f';
	
	fwrite(&fd1, sizeof(fd1), 1, fptr);
	//printf("%ld", fd1.llocation_block_no);
	//Update bit map by passing block no. of occupied block
	bitmapUpdate(a, 1);
	//inserting into naray
	insert_node(&fd1,root);
	//inserting into hashtable
	insertHashTable(&ht1, &fd1);
	//inserting into BST
	insertBst(&fd1);
	return 10;
}
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
		return -1;
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

//statistics
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
