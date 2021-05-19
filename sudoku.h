#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdint.h>

struct Sudoku {
	uint8_t cells[81];
};



void SudokuSet(struct Sudoku* board, uint8_t val, uint32_t x, uint32_t y);
uint8_t SudokuGet(struct Sudoku* board, uint32_t x, uint32_t y);
void SudokuResetPosition(struct Sudoku* board, uint32_t x, uint32_t y);
void SudokuResetBoard(struct Sudoku* board);
void SudokuPrint(const struct Sudoku* board);

int SudokuCheck(const struct Sudoku* board);
void SudokuListNeighbouringCells(const struct Sudoku* board, uint8_t* alreadySetValues, uint32_t x, uint32_t y);

#endif
