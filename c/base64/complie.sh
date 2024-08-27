gcc -c base64.c -o base64.o
ar src libbase64.a base64.o
gcc main.c -L . -l base64 -o main
