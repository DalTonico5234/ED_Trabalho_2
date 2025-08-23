all: compile run

debug: debug_compile clean debug_run

compile:
	gcc *.c -o main

debug_compile:
	gcc *.c -c -Wall -Wextra -Werror 
	gcc *.o -o main

run: 
	./main teste.txt

debug_run:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./main teste.txt

clean:
	rm *.o