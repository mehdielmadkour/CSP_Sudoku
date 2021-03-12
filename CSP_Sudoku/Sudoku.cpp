#include "Sudoku.h"


Sudoku::Sudoku() {}

Sudoku::Sudoku(const string& file) {
	fstream fs;
	fs.open(file, fstream::in);

	string line;
	int l = -1;
	while (getline(fs, line)) {
		
		if (line.find("---!---!---") == std::string::npos) {
			l++;
			line.erase(3, 1);
			line.erase(6, 1);
			
			for (int k = 0; k < 9; k++) {
				char characer = line.at(k);
				if (characer - '0' == -2) {
					startingGrid[l][k] = -1;
					grid[l][k] = -1;
				}
				else {
					startingGrid[l][k] = characer - '0';
					grid[l][k] = characer - '0';
				}
			}
		}
	}
}

void Sudoku::set(int i, int j, int value) {
	this->grid[i][j] = value;
}

int Sudoku::get(int i, int j) {
	return this->grid[i][j];
}

char Sudoku::getChar(int i, int j, int grid[9][9]) {
	if (this->grid[i][j] == -1) return ' ';
	else return this->grid[i][j] + 48;
}

void Sudoku::print(int grid[9][9]) {
	for (int i = 0; i < 9; i++) {
		cout << getChar(i, 0, grid) << "|" << getChar(i, 1, grid) << "|" << getChar(i, 2, grid) << " | " << getChar(i, 3, grid) << "|" << getChar(i, 4, grid) << "|" << getChar(i, 5, grid) << " | " << getChar(i, 6, grid) << "|" << getChar(i, 7, grid) << "|" << getChar(i, 8, grid) << endl;
		if (i == 2 || i == 5) {
			cout << "======|=======|=======" << endl;
		}
		else {
			if (i != 8) cout << "-|-|- | -|-|- | -|-|-" << endl;
		}
	}
}

void Sudoku::printStartingGrid() {
	print(this->startingGrid);
}

void Sudoku::printGrid() {
	print(this->grid);
}

list<int> Sudoku::getLegalValues(int i, int j) {

	bool isLegal[] = { true, true, true, true, true, true, true, true, true };
	list<int> legalValues;

	for (int k = 0; k < 9; k++) {
		// parcours la ligne
		int value = get(i, k);
		if (value != -1) isLegal[value - 1] = false;
		
		// parcours la colonne
		value = get(k, j);
		if (value != -1) isLegal[value - 1] = false;
	}

	// parcours le carr� 1
	if (i < 3 && j < 3) {
		if (get(0, 0) != -1) isLegal[get(0, 0) - 1] = false;
		if (get(1, 0) != -1) isLegal[get(1, 0) - 1] = false;
		if (get(2, 0) != -1) isLegal[get(2, 0) - 1] = false;
		if (get(0, 1) != -1) isLegal[get(0, 1) - 1] = false;
		if (get(1, 1) != -1) isLegal[get(1, 1) - 1] = false;
		if (get(2, 1) != -1) isLegal[get(2, 1) - 1] = false;
		if (get(0, 2) != -1) isLegal[get(0, 2) - 1] = false;
		if (get(1, 2) != -1) isLegal[get(1, 2) - 1] = false;
		if (get(2, 2) != -1) isLegal[get(2, 2) - 1] = false;
	}
	// parcours le carr� 2
	if (i < 3 && j > 2 && j < 6) {
		if (get(0, 3) != -1) isLegal[get(0, 3) - 1] = false;
		if (get(1, 3) != -1) isLegal[get(1, 3) - 1] = false;
		if (get(2, 3) != -1) isLegal[get(2, 3) - 1] = false;
		if (get(0, 4) != -1) isLegal[get(0, 4) - 1] = false;
		if (get(1, 4) != -1) isLegal[get(1, 4) - 1] = false;
		if (get(2, 4) != -1) isLegal[get(2, 4) - 1] = false;
		if (get(0, 5) != -1) isLegal[get(0, 5) - 1] = false;
		if (get(1, 5) != -1) isLegal[get(1, 5) - 1] = false;
		if (get(2, 5) != -1) isLegal[get(2, 5) - 1] = false;
	}
	// parcours le carr� 3
	if (i < 3 && j > 5) {
		if (get(0, 6) != -1) isLegal[get(0, 6) - 1] = false;
		if (get(1, 6) != -1) isLegal[get(1, 6) - 1] = false;
		if (get(2, 6) != -1) isLegal[get(2, 6) - 1] = false;
		if (get(0, 7) != -1) isLegal[get(0, 7) - 1] = false;
		if (get(1, 7) != -1) isLegal[get(1, 7) - 1] = false;
		if (get(2, 7) != -1) isLegal[get(2, 7) - 1] = false;
		if (get(0, 8) != -1) isLegal[get(0, 8) - 1] = false;
		if (get(1, 8) != -1) isLegal[get(1, 8) - 1] = false;
		if (get(2, 8) != -1) isLegal[get(2, 8) - 1] = false;
	}
	// parcours le carr� 4
	if (i > 2 && i < 6 && j < 3) {
		if (get(3, 0) != -1) isLegal[get(3, 0) - 1] = false;
		if (get(3, 0) != -1) isLegal[get(3, 0) - 1] = false;
		if (get(3, 0) != -1) isLegal[get(3, 0) - 1] = false;
		if (get(4, 1) != -1) isLegal[get(4, 1) - 1] = false;
		if (get(4, 1) != -1) isLegal[get(4, 1) - 1] = false;
		if (get(4, 1) != -1) isLegal[get(4, 1) - 1] = false;
		if (get(5, 2) != -1) isLegal[get(5, 2) - 1] = false;
		if (get(5, 2) != -1) isLegal[get(5, 2) - 1] = false;
		if (get(5, 2) != -1) isLegal[get(5, 2) - 1] = false;
	}
	// parcours le carr� 5
	if (i > 2 && i < 6 && j > 2 && j < 6) {
		if (get(3, 3) != -1) isLegal[get(3, 3) - 1] = false;
		if (get(3, 3) != -1) isLegal[get(3, 3) - 1] = false;
		if (get(3, 3) != -1) isLegal[get(3, 3) - 1] = false;
		if (get(4, 4) != -1) isLegal[get(4, 4) - 1] = false;
		if (get(4, 4) != -1) isLegal[get(4, 4) - 1] = false;
		if (get(4, 4) != -1) isLegal[get(4, 4) - 1] = false;
		if (get(5, 5) != -1) isLegal[get(5, 5) - 1] = false;
		if (get(5, 5) != -1) isLegal[get(5, 5) - 1] = false;
		if (get(5, 5) != -1) isLegal[get(5, 5) - 1] = false;
	}
	// parcours le carr� 6
	if (i > 2 && i < 6 && j > 5) {
		if (get(3, 6) != -1) isLegal[get(3, 6) - 1] = false;
		if (get(3, 6) != -1) isLegal[get(3, 6) - 1] = false;
		if (get(3, 6) != -1) isLegal[get(3, 6) - 1] = false;
		if (get(4, 7) != -1) isLegal[get(4, 7) - 1] = false;
		if (get(4, 7) != -1) isLegal[get(4, 7) - 1] = false;
		if (get(4, 7) != -1) isLegal[get(4, 7) - 1] = false;
		if (get(5, 8) != -1) isLegal[get(5, 8) - 1] = false;
		if (get(5, 8) != -1) isLegal[get(5, 8) - 1] = false;
		if (get(5, 8) != -1) isLegal[get(5, 8) - 1] = false;
	}
	// parcours le carr� 7
	if (i > 5 && j < 3) {
		if (get(6, 0) != -1) isLegal[get(6, 0) - 1] = false;
		if (get(6, 0) != -1) isLegal[get(6, 0) - 1] = false;
		if (get(6, 0) != -1) isLegal[get(6, 0) - 1] = false;
		if (get(7, 1) != -1) isLegal[get(7, 1) - 1] = false;
		if (get(7, 1) != -1) isLegal[get(7, 1) - 1] = false;
		if (get(7, 1) != -1) isLegal[get(7, 1) - 1] = false;
		if (get(8, 2) != -1) isLegal[get(8, 2) - 1] = false;
		if (get(8, 2) != -1) isLegal[get(8, 2) - 1] = false;
		if (get(8, 2) != -1) isLegal[get(8, 2) - 1] = false;
	}
	// parcours le carr� 8
	if (i > 5 && j > 2 && j < 6) {
		if (get(6, 3) != -1) isLegal[get(6, 3) - 1] = false;
		if (get(6, 3) != -1) isLegal[get(6, 3) - 1] = false;
		if (get(6, 3) != -1) isLegal[get(6, 3) - 1] = false;
		if (get(7, 4) != -1) isLegal[get(7, 4) - 1] = false;
		if (get(7, 4) != -1) isLegal[get(7, 4) - 1] = false;
		if (get(7, 4) != -1) isLegal[get(7, 4) - 1] = false;
		if (get(8, 5) != -1) isLegal[get(8, 5) - 1] = false;
		if (get(8, 5) != -1) isLegal[get(8, 5) - 1] = false;
		if (get(8, 5) != -1) isLegal[get(8, 5) - 1] = false;
	}
	// parcours le carr� 9
	if (i > 5 && j > 5) {
		if (get(6, 6) != -1) isLegal[get(6, 6) - 1] = false;
		if (get(6, 6) != -1) isLegal[get(6, 6) - 1] = false;
		if (get(6, 6) != -1) isLegal[get(6, 6) - 1] = false;
		if (get(7, 7) != -1) isLegal[get(7, 7) - 1] = false;
		if (get(7, 7) != -1) isLegal[get(7, 7) - 1] = false;
		if (get(7, 7) != -1) isLegal[get(7, 7) - 1] = false;
		if (get(8, 8) != -1) isLegal[get(8, 8) - 1] = false;
		if (get(8, 8) != -1) isLegal[get(8, 8) - 1] = false;
		if (get(8, 8) != -1) isLegal[get(8, 8) - 1] = false;
	}

	// liste les valeurs l�gales
	for (int k = 0; k < 9; k++) {
		if (isLegal[k]) legalValues.push_back(k+1);
	}

	return legalValues;
}

int Sudoku::countLegalValues(int i, int j) {
	list<int> legalValues = getLegalValues(i, j);
	return legalValues.size();
}

list<Pair> Sudoku::getEmptyCells() {
	list<Pair> empty;

	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			if (get(i, j) == -1) empty.emplace_back(i, j);
	return empty;
}

Sudoku Sudoku::copy() {
	Sudoku copy = Sudoku();
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++) {
			copy.grid[i][j] = this->grid[i][j];
			copy.startingGrid[i][j] = this->startingGrid[i][j];
		}
	return copy;
}