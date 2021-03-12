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

Pair Agent::MinimumRemainingValues(Sudoku sdk) {
	
	list<Pair> empty = sdk.getEmptyCells();
	Pair var = empty.front();
	empty.pop_front();
	int legalValueCounter = sdk.countLegalValues(var.first, var.second);

	while (!empty.empty()) {
		Pair varExplored = empty.front();
		empty.pop_front();
		int legalValueCounterExplored = sdk.countLegalValues(varExplored.first, varExplored.second);

		if (legalValueCounterExplored < legalValueCounter) {
			legalValueCounter = legalValueCounterExplored;
			var = varExplored;
		}
	}

	return var;
}

Pair Agent::DegreeHeuristic(Sudoku sdk) {
	
	list<Pair> empty = sdk.getEmptyCells();
	Pair var = empty.front();
	empty.pop_front();
	int constraintCounter = countConstraints(sdk);

	while (!empty.empty()) {
		Pair varExplored = empty.front();
		empty.pop_front();
		Sudoku copy = sdk.copy();
		list<int> legalValues = sdk.getLegalValues(varExplored.first, varExplored.second);
		//cout << legalValues.size() << endl;
		if (!legalValues.empty()) {
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

int Agent::countConstraints(Sudoku sdk) {
	list<Pair> empty = sdk.getEmptyCells();
	Pair var = empty.front();
	empty.pop_front();
	int constraintCounter = 9 - sdk.countLegalValues(var.first, var.second);

	while (!empty.empty()) {
		Pair varExplored = empty.front();
		empty.pop_front();
		constraintCounter += 9 - sdk.countLegalValues(varExplored.first, varExplored.second);
	}

	return constraintCounter;
}

Sudoku Agent::backtrackingSearch(Sudoku sdk) {
	pair<Sudoku, bool> result = recursiveBacktrackingSearch(sdk);
	return result.first;
}

pair<Sudoku, bool> Agent::recursiveBacktrackingSearch(Sudoku sudoku) {
	list<Pair> empty = sudoku.getEmptyCells();
	if (empty.empty()) return make_pair(sudoku, true);

	Pair var = MinimumRemainingValues(sudoku);
	//Pair var = DegreeHeuristic(sudoku);
	list<int> legalValues = sudoku.getLegalValues(var.first, var.second);
	while (!legalValues.empty()) {
		
		int value = legalValues.front();
		legalValues.pop_front();

		Sudoku copy = sudoku.copy();
		copy.set(var.first, var.second, value);
		
		pair<Sudoku, bool> result = recursiveBacktrackingSearch(copy);

		if (result.second){
            return result;
		}
	}
	return make_pair(sudoku, false);
}