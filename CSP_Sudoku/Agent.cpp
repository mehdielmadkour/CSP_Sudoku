#include "Agent.h"

Agent::Agent(Sudoku sudoku) {
	this->sudoku = sudoku;

	Sudoku result = backtrackingSearch(sudoku);

	cout << "---------------------" << endl;
	cout << "   Grille initiale" << endl;
	cout << "---------------------" << endl;
	sudoku.printStartingGrid();
	cout << endl;
	cout << "---------------------" << endl;
	cout << "    Grille finale    " << endl;
	cout << "---------------------" << endl;
	cout << endl;
	result.printGrid();
}

Pair Agent::MinimumRemainingValues(Sudoku sudoku) {
	
	list<Pair> empty = sudoku.getEmptyCells();
	Pair var = empty.front();
	empty.pop_front();
	int legalValueCounter = sudoku.countLegalValues(var.first, var.second);

	while (empty.size() > 0) {
		Pair varExplored = empty.front();
		empty.pop_front();
		int legalValueCounterExplored = sudoku.countLegalValues(varExplored.first, varExplored.second);

		if (legalValueCounterExplored < legalValueCounter) {
			legalValueCounter = legalValueCounterExplored;
			var = varExplored;
		}
	}

	return var;
}

Pair Agent::DegreeHeuristic(Sudoku sudoku) {
	
	list<Pair> empty = sudoku.getEmptyCells();
	Pair var = empty.front();
	empty.pop_front();
	int constraintCounter = countConstraints(sudoku);

	while (empty.size() > 0) {
		Pair varExplored = empty.front();
		empty.pop_front();
		Sudoku copy = sudoku.copy();
		list<int> legalValues = sudoku.getLegalValues(varExplored.first, varExplored.second);
		//cout << legalValues.size() << endl;
		if (legalValues.size() != 0) {
			copy.set(varExplored.first, varExplored.second, legalValues.front());
			int constraintCounterExplored = countConstraints(copy);

			if (constraintCounterExplored > constraintCounter) {
				constraintCounter = constraintCounterExplored;
				var = varExplored;
			}
		}
	}

	return var;
}

int Agent::countConstraints(Sudoku sudoku) {
	list<Pair> empty = sudoku.getEmptyCells();
	Pair var = empty.front();
	empty.pop_front();
	int constraintCounter = 9 - sudoku.countLegalValues(var.first, var.second);

	while (empty.size() > 0) {
		Pair varExplored = empty.front();
		empty.pop_front();
		constraintCounter += 9 - sudoku.countLegalValues(varExplored.first, varExplored.second);
	}

	return constraintCounter;
}

Sudoku Agent::backtrackingSearch(Sudoku sudoku) {
	pair<Sudoku, bool> result = recursiveBacktrackingSearch(sudoku);
	return result.first;
}

pair<Sudoku, bool> Agent::recursiveBacktrackingSearch(Sudoku sudoku) {
	list<Pair> empty = sudoku.getEmptyCells();
	if (empty.size() == 0) return make_pair(sudoku, true);

	Pair var = MinimumRemainingValues(sudoku);
	//Pair var = DegreeHeuristic(sudoku);
	list<int> legalValues = sudoku.getLegalValues(var.first, var.second);
	while (legalValues.size() != 0) {
		
		int value = legalValues.front();
		legalValues.pop_front();

		Sudoku copy = sudoku.copy();
		copy.set(var.first, var.second, value);
		
		pair<Sudoku, bool> result = recursiveBacktrackingSearch(copy);

		if (result.second != false) return result;
	}
	return make_pair(sudoku, false);
}