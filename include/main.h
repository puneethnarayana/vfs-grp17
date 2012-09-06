typedef struct Block {
char lfixed_size_buffer[100];
long lnext_file_blocks;
};

typedef struct Free_List {
long lblock_no;
struct Free_List *cpnext_free_block_no;
};

typedef struct File_Descriptor {
char *sfile_name;
char *slocation_full_path;
char *sfile_type;
long lfile_size;
long llocation_block_no;
};

typedef struct Main_Header {
char *sfile_system_label;
long lsize;
long ltotal_file_descriptors;
long lused_file_descriptors;
long ltotal_file_blocks;
struct File_Descriptor *cpfile_descriptor;
struct Free_List *cpfree_list;
};

void createVFS(char* , long);
