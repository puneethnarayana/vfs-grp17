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
			else {
				printf("invalid command\n");
			}
			printf("VFS-#17$ ");
			scanf("%s",cmdinput);
	}
	return 0;	
}

	
