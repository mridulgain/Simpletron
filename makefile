all : main.o check_syntax.o
	cc main.c check_syntax.c
main.o : main.c syntax.h
	cc main.c -c
check_syntax.o : check_syntax.c syntax.h
	cc check_syntax.c -c
clear:
	rm -rf *.o
	rm -rf a.out
