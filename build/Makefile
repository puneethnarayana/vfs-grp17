../bin/vfs_17.o: ../src/vfs_17.c ../include/vfs_17.h
	gcc -c ../src/vfs_17.c -o ../bin/vfs_17.o
../bin/nary.o: ../src/nary.c ../include/nary.h
	gcc -c ../src/nary.c -o ../bin/nary.o
../bin/bst.o: ../src/bst.c ../include/bst.h
	gcc -c ../src/bst.c -o ../bin/bst.o
../bin/linkedlist.o: ../src/linkedlist.c ../include/linkedlist.h
	gcc -c ../src/linkedlist.c -o ../bin/linkedlist.o
../bin/hashtable.o: ../src/hashtable.c ../include/hashtable.h
	gcc -c ../src/hashtable.c -o ../bin/hashtable.o
../bin/vfsdriver.o: ../test/vfsdriver.c ../include/vfs_17.h ../include/nary.h ../include/bst.h ../include/linkedlist.h ../include/hashtable.h ../include/vfs_errorcodes.h
	gcc -c ../test/vfsdriver.c -o ../bin/vfsdriver.o
finalout: ../bin/vfs_17.o ../bin/nary.o ../bin/bst.o ../bin/linkedlist.o ../bin/hashtable.o ../bin/vfsdriver.o
	gcc ../bin/vfs_17.o ../bin/nary.o ../bin/bst.o ../bin/linkedlist.o ../bin/hashtable.o ../bin/vfsdriver.o -o ../bin/vfs_17
