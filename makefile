all : main.o check_syntax.o Validate.o
	cc main.c check_syntax.c Validate.c
main.o : main.c syntax.h
	cc main.c -c
check_syntax.o : check_syntax.c syntax.h
	cc check_syntax.c -c
Validate.o : Validate.c 
	cc Validate.c -c
clear:
	rm -rf *.o
	rm -rf a.out
