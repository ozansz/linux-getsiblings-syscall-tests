all: einval eperm esrch fork

einval:
	gcc -o einval einval.c

eperm:
	gcc -o eperm eperm.c

esrch:
	gcc -o esrch esrch.c

fork:
	gcc -o fork fork.c

clean:
	rm -f einval eperm esrch fork

test:
	./einval && ./eperm && ./esrch && ./fork

.PHONY: all clean test