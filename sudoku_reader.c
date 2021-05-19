#include "sudoku_reader.h"
#include <stdio.h>



void ReadSudoku(struct Sudoku* sudoku, const char* filepath) {

	FILE* file = fopen(filepath, "r");
	if(!file) {
		fprintf(stderr, "Failed to open file %s\n", filepath);
		return;
	}


	char line[256];
	uint32_t cellIterator = 0;
	while(!feof(file)) {
		fgets(line, sizeof(line), file);

		char* it = line;

		while(*it) {
			if(*it >= '1' && *it <= '9') {
				sudoku->cells[cellIterator] = *it - '0';
				cellIterator++;
			}else if(*it == '.') {
				sudoku->cells[cellIterator] = 0;
				cellIterator++;
			}


			it++;
		}
		if(cellIterator >= 81)
			break;

	}


	fclose(file);
}
