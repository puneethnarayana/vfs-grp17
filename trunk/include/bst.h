	#define Success 1
	#define Failure 0
	
	struct node {
		char full_path[100];
		struct File_Descriptor *fd1;
		struct node* left;
		struct node* right;
		struct node* parent;
	};
	
	struct node* bstRoot = NULL;
	
	void insertBst(struct File_Descriptor *data );
	void inorder(struct node *t);
	void displayList();
	int searchBst(char *data);
	struct node* searchBstRec(struct node *t,char *data);
	void transplantTree(struct node *delNode,struct node *delNodeChild);
	void deleteElm(struct node *t,char *data);
