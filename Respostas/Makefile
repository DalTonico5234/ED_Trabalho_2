all:

debug_compacta: debug_compile_compacta clean debug_run_compacta

compile_compacta:
	gcc arvore.c bitmap.c lista.c io.c compactador.c compacta.c -o compacta

debug_compile_compacta:
	gcc arvore.c bitmap.c lista.c io.c compactador.c compacta.c -c -Wall -Wextra -Werror 
	gcc arvore.o bitmap.o lista.o io.o compactador.o compacta.o -o compacta

run_compacta: 
	./compacta teste.txt >saida.txt

debug_run_compacta:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./compacta teste.txt >saida.txt

clean:
	rm *.o

compacta: compile_compacta run_compacta

debug_descompacta: debug_compile_descompacta clean debug_run_descompacta

compile_descompacta:
	gcc arvore.c bitmap.c lista.c io.c descompactador.c descompacta.c -o descompacta

debug_compile_descompacta:
	gcc arvore.c bitmap.c lista.c io.c descompactador.c descompacta.c -c -Wall -Wextra -Werror 
	gcc arvore.o bitmap.o lista.o io.o descompactador.o descompacta.o -o descompacta

run_descompacta: 
	./descompacta teste.txt >saida.txt

debug_run_descompacta:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./descompacta teste.txt.comp >saida.txt

descompacta: compile_descompacta run_descompacta