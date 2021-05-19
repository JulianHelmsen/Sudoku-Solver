#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"
#include "sudoku_reader.h"

uint32_t FindEmptyPosition(const struct Sudoku* board, uint32_t currPos) {
	for(uint32_t i = currPos; i < 81; i++) {
		if(!board->cells[i])
			return i;
	}
	return 0xFFFFFFFF;
}


int Solve(struct Sudoku* board, uint32_t pos) {
	// list all possible moves
	uint32_t y = pos / 9;
	uint32_t x = pos % 9;

	uint8_t alreadySetValues[9] = { 0 };
	SudokuListNeighbouringCells(board, alreadySetValues, x, y);

	for(uint8_t i = 0; i < 9; i++) {
		if(alreadySetValues[i])
			continue;

		uint8_t move = i + 1;
		SudokuSet(board, move, x, y);
		uint32_t nextPos = FindEmptyPosition(board, pos + 1);
		if(nextPos == 0xFFFFFFFF)
			return 1;
		if(Solve(board, nextPos))
			return 1;
		
		SudokuResetPosition(board, x, y);
	}

	return 0;	
}

int main(const int argc, const char** argv) {
	if(argc == 1) {
		printf("no file given\n");
		return -1;
	}
	struct Sudoku sudoku = { 0 };
	
	
	ReadSudoku(&sudoku, argv[1]);


	SudokuPrint(&sudoku);
	puts("\n----------------------------\n");

	int solution = Solve(&sudoku, FindEmptyPosition(&sudoku, 0));
	printf("possible solution found? -> %s\n", solution ? "true" : "false");


	SudokuPrint(&sudoku);

	printf("valid: %s\n", SudokuCheck(&sudoku) ? "true" : "false");

	return 0;
}
