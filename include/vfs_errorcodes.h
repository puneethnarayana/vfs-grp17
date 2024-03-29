/*
 * VFS Error codes
 * Last updated: 15-Nov-2012
 */
#define ERR_VFS_CREATE_00 "VFS_INSUFFICIENT_ARGUMENTS" //New  (if the argument is not specified) //done
#define ERR_VFS_CREATE_01 "DATA_FILE_ALREADY_EXISTS" //done
#define ERR_VFS_CREATE_02 "CANNOT_CREATE_DATAFILE" //done
/* #define ERR_VFS_CREATE_03 "NOT_ENOUGH_MEMORY"        //redundant with error 2? */
#define ERR_VFS_CREATE_04 "INVALID_CHARACTER_IN_NAME" // The slash (/) character is not allowed //done
#define ERR_VFS_CREATE_05 "INVALID_SIZE"  // Valid range for size is 1 to 1024 (inclusive) //done
#define ERR_VFS_CREATE_07 "VFS_LABEL_TOO_LARGE" //New   (If label name exceeds 30 characters) //done

#define ERR_VFS_MOUNT_00 "VFS_INSUFFICIENT_ARGUMENTS" //New //done
#define ERR_VFS_MOUNT_01 "DATA_FILE_NOT_FOUND" //done
#define ERR_VFS_MOUNT_02 "CANNOT_READ_FROM_FILE" //redundant with error 3? //done
/* #define ERR_VFS_MOUNT_03 "INVALID_HEADER" */
#define ERR_VFS_MOUNT_04 "VFS_ALREADY_MOUNTED" //New //done

#define ERR_VFS_UNMOUNT_00 "VFS_INSUFFICIENT_ARGUMENTS" //New
#define ERR_VFS_UNMOUNT_01 "DATA_FILE_NOT_FOUND"
//#define ERR_VFS_UNMOUNT_02 "ACCESS_DENIED" 
#define ERR_VFS_UNMOUNT_03 "CANNOT_WRITE_TO_FILE" // Is it necessary as we are not dealing with file permissions?
#define ERR_VFS_UNMOUNT_04 "VFS_NOT_MOUNTED" //New 

#define ERR_VFS_MAKEDIR_00 "VFS_INSUFFICIENT_ARGUMENTS" //done
#define ERR_VFS_MAKEDIR_01 "FILESYSTEM_FULL"  //changed to FILESYSTEM_FULL from UNABLE_TO_CREATE_NEWDIR //done
#define ERR_VFS_MAKEDIR_02 "INVALID_CHARACTER_IN_DIRNAME" //done
#define ERR_VFS_MAKEDIR_03 "DIRECTORY_ALREADY_EXISTS" //done
#define ERR_VFS_MAKEDIR_05 "VFS_NOT_MOUNTED" //New //done

#define ERR_VFS_DELETEDIR_00 "VFS_INSUFFICIENT_ARGUMENTS" //done
#define ERR_VFS_DELETEDIR_01 "CANNOT_FIND_SPECIFIED_PATH_OR_DIR" //done
#define ERR_VFS_DELETEDIR_02 "DIRECTORY_IS_NOT_EMPTY"   //not valid if recursive delete is to be done //done
//#define ERR_VFS_DELETEDIR_03 "INVALID_DIRNAME" //if a filename is specified here. or should this be clubbed with error 1?
#define ERR_VFS_DELETEDIR_04 "VFS_NOT_MOUNTED" //New //done

#define ERR_VFS_MOVEDIR_00 "VFS_INSUFFICIENT_ARGUMENTS" //done
#define ERR_VFS_MOVEDIR_01 "CANNOT_FIND_SPECIFIED_SOURCEDIR" //done
#define ERR_VFS_MOVEDIR_02 "CANNOT_FIND_SPECIFIED_DESTINATIONDIR" //(if specified dir is not there, it is not created in this case unlike in add dir) //done
#define ERR_VFS_MOVEDIR_04 "SOURCE_CANNOT_BE_FILE" //done
#define ERR_VFS_MOVEDIR_05 "DESTINATION_ALREADY_HAVE_SOURCE_DIR"
#define ERR_VFS_MOVEDIR_06 "CANNOT_MOVE_PARENT_TO_CHILD_DIR"  //New 
#define ERR_VFS_MOVEDIR_07 "DESTINATION_CANNOT_BE_FILE"   //New //done
#define ERR_VFS_MOVEDIR_08 "VFS_NOT_MOUNTED" //New //done

#define ERR_VFS_LISTDIR_00 "VFS_INSUFFICIENT_ARGUMENTS" //done
#define ERR_VFS_LISTDIR_01 "CANNOT_FIND_SPECIFIED_PATH_OR_DIR" //done
#define ERR_VFS_LISTDIR_02 "INVALID_FLAG" //done
#define ERR_VFS_LISTDIR_04 "CANNOT_CREATE_OUTPUTFILE" //done
#define ERR_VFS_LISTDIR_03 "VFS_NOT_MOUNTED" //New //done

#define ERR_VFS_ADDFILE_00 "VFS_INSUFFICIENT_ARGUMENTS" //done
//#define ERR_VFS_ADDFILE_01 "UNABLE_TO_CREATE_NEWFILE" //Redundant with error 4? //done
#define ERR_VFS_ADDFILE_02 "INVALID_CHARACTER_IN_FILENAME" //done
#define ERR_VFS_ADDFILE_03 "FILE_ALREADY_EXISTS" //done
#define ERR_VFS_ADDFILE_04 "FILE_SYSTEM_FULL"   //done
#define ERR_VFS_ADDFILE_05 "CANNOT_OPEN_SPECIFIED_DATAFILE" //New //done
#define ERR_VFS_ADDFILE_06 "FILE_TOO_LARGE" //New : (if data exceeds block size) //done
#define ERR_VFS_ADDFILE_07 "VFS_NOT_MOUNTED" //New //done

#define ERR_VFS_LISTFILE_00 "VFS_INSUFFICIENT_ARGUMENTS" //done
#define ERR_VFS_LISTFILE_01 "SOURCE_FILE_PATH_NOT_FOUND" //done
#define ERR_VFS_LISTFILE_02 "CANNOT_CREATE_OUTPUTFILE" //done
#define ERR_VFS_LISTFILE_05 "NOT_A_TEXT_FILE" //done
#define ERR_VFS_LISTFILE_06 "VFS_NOT_MOUNTED" //New //done

#define ERR_VFS_UPDATEFILE_00 "VFS_INSUFFICIENT_ARGUMENTS" //done
#define ERR_VFS_UPDATEFILE_01 "INTERNAL_FILE_NOT_FOUND" //done
#define ERR_VFS_UPDATEFILE_02 "EXTERNAL_FILE_NOT_FOUND" //done
#define ERR_VFS_UPDATEFILE_04 "EXTERNAL_FILE_TOO_LARGE" //New Error Code //done
#define ERR_VFS_UPDATEFILE_05 "FILE_FORMAT_MISMATCH" //done
#define ERR_VFS_UPDATEFILE_06 "VFS_NOT_MOUNTED" //New //done

#define ERR_VFS_REMOVEFILE_00 "VFS_INSUFFICIENT_ARGUMENTS" //done
#define ERR_VFS_REMOVEFILE_01 "CANNOT_FIND_SPECIFIED_FILE" //done
#define ERR_VFS_REMOVEFILE_02 "VFS_NOT_MOUNTED" //New //done

#define ERR_VFS_MOVEFILE_00 "VFS_INSUFFICIENT_ARGUMENTS" //done
#define ERR_VFS_MOVEFILE_01 "CANNOT_FIND_SOURCEFILE" //done
#define ERR_VFS_MOVEFILE_02 "CANNOT_FIND_DESTINATION_PATH" //DESTINATION_FILE CHANGED TO DESTINATION_PATH //done
#define ERR_VFS_MOVEFILE_05 "DESTINATION_CANNOT_BE_FILE" //New //done
#define ERR_VFS_MOVEFILE_06 "VFS_NOT_MOUNTED" //New //done

#define ERR_VFS_COPYFILE_00 "VFS_INSUFFICIENT_ARGUMENTS" //done
#define ERR_VFS_COPYFILE_01 "CANNOT_FIND_SOURCEFILE" //done
#define ERR_VFS_COPYFILE_02 "CANNOT_FIND_DESTINATIONFILE"//done
#define ERR_VFS_COPYFILE_05 "CANNOT_COPY_DIR_TO_FILE" //done
#define ERR_VFS_COPYFILE_06 "FILE_SYSTEM_FULL" //done
#define ERR_VFS_COPYFILE_07 "VFS_NOT_MOUNTED" //New //done

#define ERR_VFS_EXPORTFILE_00 "VFS_INSUFFICIENT_ARGUMENTS" //done
#define ERR_VFS_EXPORTFILE_01 "CANNOT_FIND_SOURCEFILE" //done
#define ERR_VFS_EXPORTFILE_02 "CANNOT_CREATE_OUTPUTFILE" //done
#define ERR_VFS_EXPORTFILE_06 "CANNOT_EXPORT_DIR" //done
#define ERR_VFS_EXPORTFILE_07 "VFS_NOT_MOUNTED" //New //done

#define ERR_VFS_SEARCHFILE_00 "VFS_INSUFFICIENT_ARGUMENTS"
#define ERR_VFS_SEARCHFILE_01 "CANNOT_CREATE_OUTPUTFILE"
#define ERR_VFS_SEARCHFILE_02 "INVALID_CHARACTER_IN_FILENAME" //done
#define ERR_VFS_SEARCHFILE_03 "VFS_NOT_MOUNTED" //New
#define ERR_VFS_SEARCHFILE_04 "NO_FILE_FOUND"