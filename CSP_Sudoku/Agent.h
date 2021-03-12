#pragma once
#include "Sudoku.h"

class Agent {
private:
	Sudoku sudoku;
	Pair MinimumRemainingValues(Sudoku sdk);
	Pair DegreeHeuristic(Sudoku sudoku);
	Pair LeastConstrainingValue(Sudoku sudoku);
	Sudoku backtrackingSearch(const Sudoku& sdk);
	pair<Sudoku, bool> recursiveBacktrackingSearch(Sudoku sudoku);
	int countConstraints(Sudoku sudoku);
public:
	explicit Agent(Sudoku sudoku);
    virtual ~Agent() = default;
};