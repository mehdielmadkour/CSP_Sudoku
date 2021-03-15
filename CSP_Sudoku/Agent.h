#pragma once
#include "Sudoku.h"
#include <list>

class Agent {
private:
	Sudoku sudoku;
	Pair MinimumRemainingValue(Sudoku sdk);
	list<Pair> MinimumRemainingValues(Sudoku sdk);
	Pair DegreeHeuristic(Sudoku sudoku);
	int LeastConstrainingValue(Sudoku sudoku, Pair var);
	Sudoku backtrackingSearch(const Sudoku& sdk);
	pair<Sudoku, bool> recursiveBacktrackingSearch(Sudoku sudoku);
	int countConstraints(Sudoku sudoku);
	int countNeighborsConstraintReduction(Sudoku sdk, Pair var);
public:
	explicit Agent(Sudoku sudoku);
    virtual ~Agent() = default;
};