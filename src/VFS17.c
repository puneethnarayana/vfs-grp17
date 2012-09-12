/***********************VFS Entry Program************************/
#include<stdio.h>
#include<string.h>
#include "../include/main.h"
#include "../include/bst.h"
#include "../include/hashtable.h"
#include "../include/linkedlist.h"
#include "../include/narray.h"
int main(int agrc, char* argv[]) {
	char cmdinput[20];
	char vfs_name[100];
	long vfs_size;
	FILE *fptr;
	char *cmdpromptmount;
	printf("VFS-#17$ ");
	scanf("%s",cmdinput);
	while(strcmp(cmdinput,"exit")){
			if(!strcmp(cmdinput,"create")) { 
				printf("VFS Name: ");
				scanf("%s", vfs_name);
				printf("VFS Size: ");
				scanf("%lu", &vfs_size);
				createVFS(vfs_name, vfs_size);
			}
			else if(!strcmp(cmdinput, "mount"))
			{
				printf("Mount VFS: ");
				scanf("%s", vfs_name);
				fptr = mount_VFS(vfs_name);
				cmdpromptmount = strcat(vfs_name,"@VFS-#17$ ");
				printf(cmdpromptmount);
				scanf("%s",cmdinput);
				while(strcmp(cmdinput,"exit")) {
					
					if(!strcmp(cmdinput,"write")) {
						write_File(vfs_name);
					}
					else if(!strcmp(cmdinput,"delete")) {
						printf("Deleted\n");
					}
					else {
						printf("invalid command\n");
					}
					printf(cmdpromptmount);
					scanf("%s",cmdinput);
						
				}
			}
			
			else if(!strcmp(cmdinput, "unmount")) {
				printf("Unmount VFS: ");
				scanf("%s", vfs_name);
				unmount_VFS(vfs_name, fptr);				
			}
			else {
				printf("invalid command\n");
				
			}
			printf("VFS-#17$ ");
			scanf("%s",cmdinput);
	}
	return 0;	
}

	
