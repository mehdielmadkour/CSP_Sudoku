#pragma once
#include <list>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <array>

using namespace std;
typedef pair<int, int> Pair;
typedef array<array<char, 9>, 9> Grid;

class Sudoku {
private:
	Grid grid;
	char getChar(int i, int y);


public:
	Sudoku();
	explicit Sudoku(const string& file);
    virtual ~Sudoku() = default;

    int get(int i, int y);
	void set(int i, int y, int value);

    void printGrid();

	int countLegalValues(int i, int j);
	list<int> getLegalValues(int i, int j);
	list<Pair> getEmptyCells();
	Sudoku copy();
};