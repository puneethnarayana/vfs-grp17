typedef struct tree_node 
{ 
struct File_Descriptor *data; 
char node_name[80];
int is_deleted; 
int left_traversed;
struct tree_node *left; 
struct tree_node *sibling; 
struct tree_node *parent; 
}t_node; 

t_node *root,*prev,*sib;

void printtree(t_node *root);
t_node* insert_node (struct File_Descriptor* data,t_node *root);
int delete(struct File_Descriptor* data,t_node *root);
t_node* nary_insert_root();
int list_tree_nonrec(t_node* retnode,char* harddiskpath);
int list_tree(t_node** root,int flag,char* fullpath,char* harddiskpath);
int list_tree_rec(t_node *root,char* harddiskpath);

