main: main.c libmd5.a
	gcc main.c -L . -l md5 -o main
libmd5.a: md5.o
	ar rsc libmd5.a md5.o
md5.o: md5.c
	gcc -c md5.c -o md5.o
