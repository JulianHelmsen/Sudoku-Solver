#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"
#include <assert.h>

uint8_t SudokuGet(struct Sudoku* board, uint32_t x, uint32_t y) {
	return board->cells[x + y * 9];
}

void SudokuSet(struct Sudoku* board, uint8_t val, uint32_t x, uint32_t y) {
	assert(val > 0  && val <= 9);
	board->cells[x + y * 9] = val;
}

void SudokuResetPosition(struct Sudoku* board, uint32_t x, uint32_t y) {
	board->cells[x + y * 9] = 0;

}

void SudokuResetBoard(struct Sudoku* board) {
	for(uint32_t i = 0; i < 81; i++)
		board->cells[i] = 0;

}

void SudokuPrint(const struct Sudoku* board) {
	char buffer[256] = {0};

	uint32_t len;
	for(uint32_t y = 0; y < 9; y++) {
		char* it = buffer;
		for(uint32_t x = 0; x < 9; x++) {
			if(x % 3 == 0 && x != 0) {
				*it = '|';
				it++;
			}
			*it = ' ';
			it++;

			uint8_t val = board->cells[x + y * 9];
			*it = val == 0 ? '.' : '0' + val;
			it++;
			*it = ' ';
			it++;
		}
		puts(buffer);
		len = it - buffer;
		if(y != 8 && (y + 1) % 3 == 0) {
			for(uint32_t i = 0; i  < len; i++)
				buffer[i] = '-';
			puts(buffer);
		}

	}

}

int SudokuCheck(const struct Sudoku* board) {


	for(uint32_t i = 0; i < 9; i++) {
		char vmap[10] = { 0 }; // vertical map
		char hmap[10] = { 0 }; // horizontal map
		for(uint32_t j = 0; j < 9; j++) {
			uint8_t vVal = board->cells[i + j * 9];
			uint8_t hVal = board->cells[j + i * 9];
			if(vmap[vVal])
				return 0;
			if(hmap[hVal])
				return 0;
			vmap[vVal] = 1;
			hmap[hVal] = 1;
			
		}
		for(uint32_t j = 1; j < 10; j++)
			if(!vmap[j] || !hmap[j])
				return 0;
	}

	// check boxes
	
	for(uint32_t x = 0; x < 9; x += 3) {
		for(uint32_t y = 0; y < 9; y += 3) {
			char map[9] = { 0 };
			// box {x, y, 3, 3}
			for(uint32_t j = 0; j < 3; j++) {
				for(uint32_t i = 0; i < 3; i++) {
					uint32_t ypos = y + j;
					uint32_t xpos = x + i;
					uint8_t val = board->cells[xpos + ypos * 9];
					if(!val)
						return 0;
					map[val - 1] = 1;
				}
			}

			for(uint32_t i = 0; i < 9; i++)
				if(!map[i])
					return 0;
		}
	}
	return 1;

}

void SudokuListNeighbouringCells(const struct Sudoku* board, uint8_t* alreadySetValues, uint32_t x, uint32_t y) {
	for(uint32_t i = 0; i < 9; i++) {
		uint32_t hVal = board->cells[i + y * 9];
		uint32_t vVal = board->cells[x + i * 9];
		if(i != x) {
			if(hVal)
				alreadySetValues[hVal - 1] = 1;
		}
		if(i != y) {
			if(vVal)
				alreadySetValues[vVal - 1] = 1;
		}
	}


	const uint32_t blockStartX = x - x % 3;
	const uint32_t blockStartY = y - y % 3;

	for(uint32_t i = 0; i < 3; i++)
		for(uint32_t j = 0; j < 3; j++) {
			uint32_t xpos = blockStartX + j;
			uint32_t ypos = blockStartY + i;
			if(xpos == x && ypos == y)
				continue;
			uint8_t val = board->cells[xpos + ypos * 9];
			if(val)
				alreadySetValues[val - 1] = 1;

		}
}
