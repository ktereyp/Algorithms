simple:simple.o calculator.o
	gcc `pkg-config --libs glu` -lglut -lm simple.o calculator.o -o simple

simple.o:simple.c

#calculator:calculator.o
#	gcc -lm calculator.o -o calculator
calculator.o:calculator.c
	gcc -ggdb calculator.c -c

clean:
	@rm *.o
	@rm simple
