/*
 * File: vfsdriver.c
 *
 * Description: This is a driver program for testing your VFS system using an interaction script as input
 * You need to make additional calls to your respective functions as noted in the comments below
 * Make sure the output you display is exactly as per the given specifications for you. Do NOT print
 * any extra output (like debug messages) in the final version of your driver program. You can use this driver program
 * in a in incremental manner as you keep implementing one operator after another. For operators not yet implemented,
 * you can leave the output as given ("TO_BE_DONE"). So you can use this program as your "main" program for testing purposes.
 *
 * DO NOT write the full code for operators in the driver program! You must only CALL your functions from here.
 *
 * Usage: vfsdriver <scriptfilename>
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../include/vfs_errorcodes.h"

#define BUFSIZE 400
#define CMDSIZE 40
#define PARSIZE 200

int errcode;

void createvfs ( char *P1, int P2 );
void mountvfs ( char *P1 );
void unmountvfs ( char *P1 );
void makedir ( char *P1, char *P2 );
void deletedir ( char *P1 );
void movedir ( char *P1, char *P2 );
void listdir ( char *P1, int P2, char *P3 );
void addfile ( char *P1, char *P2, char *P3 );
void listfile ( char *P1, char *P2 );
void updatefile ( char *P1, char *P2 );
void removefile ( char *P1 );
void movefile ( char *P1, char *P2 );
void copyfile ( char *P1, char *P2 );
void exportfile ( char *P1, char *P2 );
void searchfile ( char *P1, char *P2 );
void man(char* P1);
void cat(char* P1);


void processcommand( char *command, char *P1, char *P2, char *P3 );

int main( int argc, char *argv[] )
{
	FILE *scriptfp;
	char linebuffer[BUFSIZE];
	char command[CMDSIZE], par1[PARSIZE], par2[PARSIZE], par3[PARSIZE];
	char *token;

	if( argc != 2 ){
		fprintf(stderr,"Usage: vfsdriver <scriptfile>\n");
		return(1);
	}

	if( (scriptfp=fopen(argv[1],"r")) == NULL ){
		fprintf(stderr,"Unable to open script file: %s\n", argv[1]);
		return(2);
	}

	while( fgets(linebuffer, sizeof(linebuffer), scriptfp) != NULL ){
		/* This output is for debugging... do not uncomment in final version */
		/*
		printf("==================================================\n");
		printf("Processing: %s", linebuffer);
		printf("==================================================\n");
		*/

		/* Remove the extra newline character in the end of line */
		linebuffer[ strlen(linebuffer)-1 ] = '\0';
		
		/* Get the command and the parameters using tokenizer */
		strcpy( command, (token = strtok(linebuffer, " ")) == NULL ? "" : token );
		
		strcpy( par1, (token = strtok(NULL, " ")) == NULL ? "" : token );
		strcpy( par2, (token = strtok(NULL, " ")) == NULL ? "" : token );
		strcpy( par3, (token = strtok(NULL, " ")) == NULL ? "" : token );
		/* printf("Command:%s:p1:%s:p2:%s:p3:%s\n",command, par1, par2, par3); */

		processcommand( command, par1, par2, par3 );
	
	}
}

void processcommand( char *command, char *P1, char *P2, char *P3 )
{
	if( strcmp(command, "createvfs") == 0 ){
		if(strcmp(P2, "") == 0) { 
			P2 == "-1";
		}
		long size = atol(P2);
		//printf("%ld", size);
		createvfs ( P1, size );
	}
	else if( strcmp(command, "mountvfs") == 0 )
		mountvfs (P1);
	else if( strcmp(command, "unmountvfs") == 0 ) {
		//printf("%s\n", P1);
		unmountvfs (P1);
	}
	else if( strcmp(command, "makedir") == 0 )
		makedir (P1,P2);
	else if( strcmp(command, "deletedir") == 0 )
		deletedir (P1);
	else if( strcmp(command, "movedir") == 0 )
		movedir (P1,P2);
	else if( strcmp(command, "listdir") == 0 ){
		//printf("here here%s\n", P3);
		if(strcmp(P3, "") == 0) { 
			P2 == "-1";
		}
		int flag = atoi(P2);
		listdir (P1,flag,P3);
		//printf("here here%s\n", P3);
	}
	else if( strcmp(command, "addfile") == 0 )
		addfile(P1, P2, P3);
	else if( strcmp(command, "listfile") == 0 )
		listfile(P1, P2);
	else if( strcmp(command, "updatefile") == 0 )
		updatefile(P1, P2);
	else if( strcmp(command, "removefile") == 0 )
		removefile (P1);
	else if( strcmp(command, "movefile") == 0 )
		movefile (P1,P2);
	else if( strcmp(command, "copyfile") == 0 )
		copyfile (P1,P2);
	else if( strcmp(command, "exportfile") == 0 )
		exportfile (P1,P2);
	else if( strcmp(command, "searchfile") == 0 )
		searchfile(P1, P2);
	else if( strcmp(command, "stats") == 0 )
		stats ();
	else if( strcmp(command, "man") == 0 )
		man (P1);
	else if( strcmp(command, "cat") == 0 )
		cat(P1);
	else
		printf("Ignoring invalid command %s\n", command);

}

void createvfs ( char *P1, int P2 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	errcode = create_VFS(P1, P2);
	if (errcode == 00) { 
		printf("createvfs_FAILURE\t");
		printf(ERR_VFS_CREATE_00);
		printf("\n");
		
	}
	else if (errcode == 01) {
		printf("createvfs_FAILURE\t");
		printf(ERR_VFS_CREATE_01);
		printf("\n");
		
	}
	else if (errcode == 02) {
		printf("createvfs_FAILURE\t");
		printf(ERR_VFS_CREATE_02);
		printf("\n");
		
	}
	/*else if (errcode == 03) {
		printf(ERR_VFS_CREATE_03);
		printf("\n");
		
	}*/
	else if (errcode == 04) {
		printf("createvfs_FAILURE\t");
		printf(ERR_VFS_CREATE_04);
		printf("\n");
	
	}
	else if (errcode == 05) {
		printf("createvfs_FAILURE\t");
		printf(ERR_VFS_CREATE_05);
		printf("\n");
		
	}
	/*else if (errcode == 06) {
		printf(ERR_VFS_CREATE_06);
		printf("\n");
		
	}*/
	else if (errcode == 07) {
		printf("createvfs_FAILURE\t");
		printf(ERR_VFS_CREATE_07);
		printf("\n");
		
	}
	else if (errcode == 10) {
		printf("createvfs_SUCCESS\n");
	}
	else {
		printf("createvfs_FAILURE\t");
		printf(ERR_VFS_CREATE_02);
		printf("\n");
	
	}
}

void mountvfs ( char *P1 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	errcode = mount_VFS(P1);
	if (errcode == 00) { 
		printf("mountvfs_FAILURE\t");
		printf(ERR_VFS_MOUNT_00);
		printf("\n");
		
	}
	else if (errcode == 01) {
		printf("mountvfs_FAILURE\t");
		printf(ERR_VFS_MOUNT_01);
		printf("\n");
		
	}
	else if (errcode == 02) {
		printf("mountvfs_FAILURE\t");
		printf(ERR_VFS_MOUNT_02);
		printf("\n");
	
	}
	else if (errcode == 04) {
		printf("mountvfs_FAILURE\t");
		printf(ERR_VFS_MOUNT_04);
		printf("\n");
		//exit(1);
	}
	else if (errcode == 10)
	printf("mountvfs_SUCCESS\n");
}

void unmountvfs ( char *P1 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	//printf("%s\n", P1);
	errcode = unmount_VFS(P1);
	if (errcode == 0) { 
		printf("unmountvfs_FAILURE\t");
		printf(ERR_VFS_UNMOUNT_00);
		printf("\n");
	
	}
	else if (errcode == 1) {
		printf("unmountvfs_FAILURE\t");
		printf(ERR_VFS_UNMOUNT_01);
		printf("\n");
		
	}
	else if (errcode == 3) {
		printf("unmountvfs_FAILURE\t");
		printf(ERR_VFS_UNMOUNT_03);
		printf("\n");
		
	}
	else if (errcode == 4) {
		printf("unmountvfs_FAILURE\t");
		printf(ERR_VFS_UNMOUNT_04);
		printf("\n");
	
	}
	else if (errcode == 10)
	printf("unmountvfs_SUCCESS\n");;
}

void makedir ( char *P1, char *P2 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	errcode = make_dir(P1, P2);
	if (errcode == 00) { 
		printf("makedir_FAILURE\t");
		printf(ERR_VFS_MAKEDIR_00);
		printf("\n");
	}
	else if (errcode == 01) { 
		printf("makedir_FAILURE\t");
		printf(ERR_VFS_MAKEDIR_01);
		printf("\n");
	}
	else if (errcode == 02) { 
		printf("makedir_FAILURE\t");
		printf(ERR_VFS_MAKEDIR_02);
		printf("\n");
	}
	else if (errcode == 03) { 
		printf("makedir_FAILURE\t");
		printf(ERR_VFS_MAKEDIR_03);
		printf("\n");
	}
	else if (errcode == 05) { 
		printf("makedir_FAILURE\t");
		printf(ERR_VFS_MAKEDIR_05);
		printf("\n");
	}
	else if (errcode == 10) {
		printf("makedir_SUCCESS\n");
	}
}

void deletedir ( char *P1 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	errcode = delete_dir(P1);
	if (errcode == 00) { 
		printf("deletedir_FAILURE\t");
		printf(ERR_VFS_DELETEDIR_00);
		printf("\n");
	}
	else if (errcode == 01) { 
		printf("deletedir_FAILURE\t");
		printf(ERR_VFS_DELETEDIR_01);
		printf("\n");
	}
	else if (errcode == 02) { 
		printf("deletedir_FAILURE\t");
		printf(ERR_VFS_DELETEDIR_02);
		printf("\n");
	}
	/*else if (errcode == 03) { 
		printf("deletedir_FAILURE\t");
		printf(ERR_VFS_DELETEDIR_03);
		printf("\n");
	}*/
	else if (errcode == 04) { 
		printf("deletedir_FAILURE\t");
		printf(ERR_VFS_DELETEDIR_04);
		printf("\n");
	}
	else if (errcode == 10) {
		printf("deletedir_SUCCESS\n");
	}
}

void movedir ( char *P1, char *P2 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	errcode = move_dir(P1, P2);
	
	if (errcode == 00) { 
		printf("movedir_FAILURE\t");
		printf(ERR_VFS_MOVEDIR_00);
		printf("\n");
	}
	else if (errcode == 01) { 
		printf("movedir_FAILURE\t");
		printf(ERR_VFS_MOVEDIR_01);
		printf("\n");
	}
	else if (errcode == 02) { 
		printf("movedir_FAILURE\t");
		printf(ERR_VFS_MOVEDIR_02);
		printf("\n");
	}
	else if (errcode == 05) { 
		printf("movedir_FAILURE\t");
		printf(ERR_VFS_MOVEDIR_05);
		printf("\n");
	}
	else if (errcode == 06) { 
		printf("movedir_FAILURE\t");
		printf(ERR_VFS_MOVEDIR_06);
		printf("\n");
	}
	else if (errcode == 07) { 
		printf("movedir_FAILURE\t");
		printf(ERR_VFS_MOVEDIR_07);
		printf("\n");
	}
	else if (errcode == 8) { 
		printf("movedir_FAILURE\t");
		printf(ERR_VFS_MOVEDIR_08);
		printf("\n");
	}
	else if(errcode == 10) {
		printf("movedir_SUCCESS\n");
	}
}

void listdir ( char *P1, int P2, char *P3 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	errcode = list_dir(P1, P2, P3);
	if (errcode == 00) { 
		printf("listdir_FAILURE\t");
		printf(ERR_VFS_LISTDIR_00);
		printf("\n");
	}
	else if (errcode == 01) { 
		printf("listdir_FAILURE\t");
		printf(ERR_VFS_LISTDIR_01);
		printf("\n");
	}
	else if (errcode == 02) { 
		printf("listdir_FAILURE\t");
		printf(ERR_VFS_LISTDIR_02);
		printf("\n");
	}
	else if (errcode == 03) { 
		printf("listdir_FAILURE\t");
		printf(ERR_VFS_LISTDIR_03);
		printf("\n");
	}
	else if (errcode == 04) { 
		printf("listdir_FAILURE\t");
		printf(ERR_VFS_LISTDIR_04);
		printf("\n");
	}
	else if(errcode == 10) {
		printf("listdir_SUCCESS\n");
	}
}

void addfile ( char *P1, char *P2, char *P3 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	errcode = add_File (P1,P2,P3);
	if (errcode == 00) { 
		printf("addfile_FAILURE\t");
		printf(ERR_VFS_ADDFILE_00);
		printf("\n");
	}
	else if (errcode == 01) {
		printf("addfile_FAILURE\t");
		printf(ERR_VFS_ADDFILE_04);
		printf("\n");
	}
	else if (errcode == 02) {
		printf("addfile_FAILURE\t");
		printf(ERR_VFS_ADDFILE_02);
		printf("\n");
	}
	else if (errcode == 03) {
		printf("addfile_FAILURE\t");
		printf(ERR_VFS_ADDFILE_03);
		printf("\n");
	}
	else if (errcode == 04) {
		printf("addfile_FAILURE\t");
		printf(ERR_VFS_ADDFILE_04);
		printf("\n");
	}
	else if (errcode == 05) {
		printf("addfile_FAILURE\t");
		printf(ERR_VFS_ADDFILE_05);
		printf("\n");
	}
	else if (errcode == 06) {
		printf("addfile_FAILURE\t");
		printf(ERR_VFS_ADDFILE_06);
		printf("\n");
	}
	else if (errcode == 07) {
		printf("addfile_FAILURE\t");
		printf(ERR_VFS_ADDFILE_07);
		printf("\n");
	}
	else if (errcode == 10) {
		printf("addfile_SUCCESS\n");
	}
}

void listfile ( char *P1, char *P2 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	errcode = list_File(P1,P2);
	if (errcode == 00) { 
		printf("listfile_FAILURE\t");
		printf(ERR_VFS_LISTFILE_00);
		printf("\n");
	}
	else if (errcode == 01) {
		printf("listfile_FAILURE\t");
		printf(ERR_VFS_LISTFILE_01);
		printf("\n");
	}
	else if (errcode == 02) {
		printf("listfile_FAILURE\t");
		printf(ERR_VFS_LISTFILE_02);
		printf("\n");
	}
	/*else if (errcode == 3) {
		printf(ERR_VFS_LISTFILE_03);
		printf("\n");
	}*/
	/*else if (errcode == 4) {
		printf(ERR_VFS_LISTFILE_04);
		printf("\n");
	}*/
	else if (errcode == 05) {
		printf("listfile_FAILURE\t");
		printf(ERR_VFS_LISTFILE_05);
		printf("\n");
	}
	else if (errcode == 06) {
		printf("listfile_FAILURE\t");
		printf(ERR_VFS_LISTFILE_06);
		printf("\n");
	}
	else if (errcode == 10)
	printf("listfile_SUCCESS\n");
}

void updatefile ( char *P1, char *P2 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	errcode = update_File(P1, P2);
	if (errcode == 00) { 
		printf("updatefile_FAILURE\t");
		printf(ERR_VFS_UPDATEFILE_00);
		printf("\n");
	}
	else if (errcode == 01) { 
		printf("updatefile_FAILURE\t");
		printf(ERR_VFS_UPDATEFILE_01);
		printf("\n");
	}
	else if (errcode == 02) { 
		printf("updatefile_FAILURE\t");
		printf(ERR_VFS_UPDATEFILE_02);
		printf("\n");
	}
	else if (errcode == 04) { 
		printf("updatefile_FAILURE\t");
		printf(ERR_VFS_UPDATEFILE_04);
		printf("\n");
	}
	else if (errcode == 05) { 
		printf("updatefile_FAILURE\t");
		printf(ERR_VFS_UPDATEFILE_05);
		printf("\n");
	}
	else if (errcode == 06) { 
		printf("updatefile_FAILURE\t");
		printf(ERR_VFS_UPDATEFILE_06);
		printf("\n");
	}
	else if (errcode == 10)
	printf("updatefile_SUCCESS\n");
}

void removefile ( char *P1 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	errcode = remove_File(P1);
	if (errcode == 00) { 
		printf("removefile_FAILURE\t");
		printf(ERR_VFS_REMOVEFILE_00);
		printf("\n");
	}
	else if (errcode == 01) {
		printf("removefile_FAILURE\t"); 
		printf(ERR_VFS_REMOVEFILE_01);
		printf("\n");
	}
	else if (errcode == 02) { 
		printf("removefile_FAILURE\t");
		printf(ERR_VFS_REMOVEFILE_02);
		printf("\n");
	}
	else if (errcode == 10)
	printf("removefile_SUCCESS\n");
}

void movefile ( char *P1, char *P2 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	errcode = move_File(P1, P2);
	if (errcode == 00) { 
		printf("movefile_FAILURE\t");
		printf(ERR_VFS_MOVEFILE_00);
		printf("\n");
	}
	else if (errcode == 01) {
		printf("movefile_FAILURE\t");
		printf(ERR_VFS_MOVEFILE_01);
		printf("\n");
	}
	else if (errcode == 02) {
		printf("movefile_FAILURE\t");
		printf(ERR_VFS_MOVEFILE_02);
		printf("\n");
	}
	else if (errcode == 05) {
		printf("movefile_FAILURE\t");
		printf(ERR_VFS_MOVEFILE_05);
		printf("\n");
	}
	else if (errcode == 06) {
		printf("movefile_FAILURE\t");
		printf(ERR_VFS_MOVEFILE_06);
		printf("\n");
	}
	else if (errcode == 10)
	printf("movefile_SUCCESS\n");
}

void copyfile ( char *P1, char *P2 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	errcode = copy_File(P1, P2);
	if (errcode == 00) { 
		printf("copyfile_FAILURE\t");
		printf(ERR_VFS_COPYFILE_00);
		printf("\n");
	}
	else if (errcode == 01) {
		printf("copyfile_FAILURE\t");
		printf(ERR_VFS_COPYFILE_01);
		printf("\n");
	}
	else if (errcode == 02) {
		printf("copyfile_FAILURE\t");
		printf(ERR_VFS_COPYFILE_02);
		printf("\n");
	}
	else if (errcode == 05) {
		printf("copyfile_FAILURE\t");
		printf(ERR_VFS_COPYFILE_05);
		printf("\n");
	}
	else if (errcode == 06) {
		printf("copyfile_FAILURE\t");
		printf(ERR_VFS_COPYFILE_06);
		printf("\n");
	}
	else if (errcode == 07) {
		printf("copyfile_FAILURE\t");
		printf(ERR_VFS_COPYFILE_07);
		printf("\n");
	}
	else if(errcode == 10)
	printf("copyfile_SUCCESS\n");
}

void exportfile ( char *P1, char *P2 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	errcode = export_File(P1, P2);
	if (errcode == 00) { 
		printf("exportfile_FAILURE\t");
		printf(ERR_VFS_EXPORTFILE_00);
		printf("\n");
	}
	else if (errcode == 01) { 
		printf("exportfile_FAILURE\t");
		printf(ERR_VFS_EXPORTFILE_01);
		printf("\n");
	}
	else if (errcode == 02) { 
		printf("exportfile_FAILURE\t");
		printf(ERR_VFS_EXPORTFILE_02);
		printf("\n");
	}
	else if (errcode == 06) { 
		printf("exportfile_FAILURE\t");
		printf(ERR_VFS_EXPORTFILE_06);
		printf("\n");
	}
	else if (errcode == 07) { 
		printf("exportfile_FAILURE\t");
		printf(ERR_VFS_EXPORTFILE_07);
		printf("\n");
	}
	else if (errcode == 10)
	printf("exportfile_SUCCESS\n");
}

void searchfile ( char *P1, char *P2 )
{
	/* Call the appropriate function with given arguments and display appropriate output on the screen */
	errcode = search_File (P1,P2);
	if (errcode == 00) { 
		printf("searchfile_FAILURE\t");
		printf(ERR_VFS_SEARCHFILE_00);
		printf("\n");
	}
	else if (errcode == 02) {
		printf("searchfile_FAILURE\t");
		printf(ERR_VFS_SEARCHFILE_02);
		printf("\n");
	}
	else if (errcode == 01) {
		printf("searchfile_FAILURE\t");
		printf(ERR_VFS_SEARCHFILE_01);
		printf("\n");
	}
	else if (errcode == 03) {
		printf("searchfile_FAILURE\t");
		printf(ERR_VFS_SEARCHFILE_03);
		printf("\n");
	}
	else if (errcode == 04) {
		printf("searchfile_FAILURE\t");
		printf(ERR_VFS_SEARCHFILE_04);
		printf("\n");
	}
	else if (errcode == 10)
	printf("searchfile_SUCCESS\n");
}
