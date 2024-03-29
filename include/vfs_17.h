struct Block {
char sfixed_size_buffer[1024];
};

struct Free_List {
char *bitmap;
};

struct File_Descriptor {
char sfile_name[100];
char slocation_full_path[512];
char sfile_type;
long lfile_size;
long llocation_block_no;
};

struct Main_Header {
char sfile_system_label[30];
long lsize;
long ltotal_file_descriptors;
long lused_file_descriptors;
long ltotal_file_blocks;
long freeblock;
long freedescriptor;
};

int createVFS(char*, long);
void bitMapInit();
long freeLocation();
void bitmapUpdate(long, int);
