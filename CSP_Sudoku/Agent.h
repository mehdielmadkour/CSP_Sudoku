#pragma once
#include "Sudoku.h"

class Agent {
private:
	Sudoku sudoku;
	Pair MinimumRemainingValues(Sudoku sudoku);
	Pair DegreeHeuristic(Sudoku sudoku);
	Pair LeastConstrainingValue(Sudoku sudoku);
	Sudoku backtrackingSearch(Sudoku sudoku); 
	pair<Sudoku, bool> recursiveBacktrackingSearch(Sudoku sudoku);
	int countConstraints(Sudoku sudoku);
public:
	Agent(Sudoku sudoku);
};