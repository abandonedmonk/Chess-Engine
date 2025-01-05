all:
	gcc -Ofast bbc.c -o bbc.exe

debug: 
	gcc bbc.c -o bbc.exe