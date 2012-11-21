typedef struct Hash_Table{
struct List_Node* Table[53];
}Hash_Table;

void initialzeHashTable(struct Hash_Table *);
int hashFunction(char);
void insertHashTable(struct Hash_Table *, struct File_Descriptor *);
struct List_Node *searchHashTable(struct Hash_Table *, char[]);
void deleteHashTable(struct Hash_Table * ,char[], char[]);
void printHashTable(struct Hash_Table *);
