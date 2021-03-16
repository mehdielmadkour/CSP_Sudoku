#pragma once
#include "Sudoku.h"
#include <list>

class Agent {
private:
	Sudoku sudoku;
	Pair MinimumRemainingValue(Sudoku sdk);
	list<Pair> MinimumRemainingValues(Sudoku sdk);
	Pair DegreeHeuristic(Sudoku sdk);
	int LeastConstrainingValue(Sudoku sdk, Pair var);
	Sudoku backtrackingSearch(const Sudoku& sdk);
    pair<Sudoku, bool> recursiveBacktracking(Sudoku sdk);
	int countConstraints(Sudoku sudoku);
public:
	explicit Agent(Sudoku sudoku);
    virtual ~Agent() = default;
};