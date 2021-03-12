#pragma once
#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>

using namespace std;
typedef pair<int, int> Pair;
class Sudoku {
private:
	int startingGrid[9][9];
	int grid[9][9];
	char getChar(int i, int y, int grid[9][9]);
	void print(int grid[9][9]);

public:
	Sudoku();
	Sudoku(string file);
	int get(int i, int y);
	void set(int i, int y, int value);
	void printStartingGrid();
	void printGrid();
	int countLegalValues(int i, int j);
	list<int> getLegalValues(int i, int j);
	list<Pair> getEmptyCells();
	Sudoku copy();
	bool isValid();
};