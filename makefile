all:
	gcc -oFast bbc.c -o bbc
	x86_64-w64-mingw32-gcc -oFast bbc.c -o bbc.exe