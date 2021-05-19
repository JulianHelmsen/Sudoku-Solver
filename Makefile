
FLAGS = -g 
CC = gcc

all: Main.c sudoku.c sudoku.h sudoku_reader.c sudoku_reader.h
	$(CC) $(FLAGS) -o Result Main.c sudoku.c sudoku_reader.c
