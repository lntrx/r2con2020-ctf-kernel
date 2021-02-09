all:
	gcc -static exploit.c -o exploit -lpthread
clean:
	@rm exploit
