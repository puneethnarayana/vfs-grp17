typedef struct Block {
char sfixed_size_buffer[1024];
};

typedef struct Free_List {
char *bitmap;
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
long freeblock;
long freedescriptor;
};

void createVFS(char* , long);
