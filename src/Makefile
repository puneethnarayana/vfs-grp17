main.o: main.c ../include/main.h
	gcc -c main.c -o main.o
narray.o: narray.c ../include/narray.h
	gcc -c narray.c -o narray.o
bst.o: bst.c ../include/bst.h
	gcc -c bst.c -o bst.o
linkedlist.o: linkedlist.c ../include/linkedlist.h
	gcc -c linkedlist.c -o linkedlist.o
hashtable.o: hashtable.c ../include/hashtable.h
	gcc -c hashtable.c -o hashtable.o
test.o: test.c ../include/main.h ../include/narray.h ../include/bst.h ../include/linkedlist.h ../include/hashtable.h 
	gcc -c test.c -o test.o
finalout: main.o narray.o bst.o linkedlist.o hashtable.o test.o
	gcc main.o narray.o bst.o linkedlist.o hashtable.o test.o -o finalout
