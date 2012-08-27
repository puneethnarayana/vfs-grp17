typedef struct Block {
long lfixed_size_buffer;
};

typedef struct Free_List {
long lblock_no;
//Free_List *cpnext_free_block_no;
};

typedef struct File_Descriptor {
char sfile_name[100];
char slocation_full_path[250];
char sfile_type[50];
long lfile_size;
long llocation_block_no;
};

typedef struct Main_Header {
char sfile_system_label[100];
long ltotal_file_descriptors;
long lused_file_descriptors;
//File_Descriptor *cpfile_descriptor;
//Free_List *cpfree_list;
};

void disp(void);
