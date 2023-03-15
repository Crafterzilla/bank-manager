bank_manager: main.c ./include/*.h ./src/*.c
	gcc -o bank_manager main.c ./src/*.c ./include/*.h -I -lm