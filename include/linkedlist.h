typedef struct List_Node {
    struct File_Descriptor *data;
    char *key;
 //pointer has to be used
   //struct fileDescriptor *Descriptor;
    struct List_Node *next;
}List_Node;

//insert element in the linked list
struct List_Node *listInsertStart( List_Node *head, char *key, struct File_Descriptor *data);

/* returns void *data correspondign to the node that matches the given key */
struct List_Node *listSearchStrKey( struct List_Node *head, char *key);

//delete a node
void listDeleteNode(struct List_Node *head, char *key, char *path);

//display list
void display(struct List_Node *head);



