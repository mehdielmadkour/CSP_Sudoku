#include "Agent.h"

Agent::Agent(Sudoku sudoku) {
	this->sudoku = sudoku;

	cout << "---------------------" << endl;
	cout << "   Grille initiale" << endl;
	cout << "---------------------" << endl;
	sudoku.printGrid();

    Sudoku result = backtrackingSearch(sudoku);

	cout << endl;
	cout << "---------------------" << endl;
	cout << "    Grille finale    " << endl;
	cout << "---------------------" << endl;
	cout << endl;
	result.printGrid();
}

Pair Agent::MinimumRemainingValue(Sudoku sdk) {

	list<Pair> empty = sdk.getEmptyCells();
	Pair var = empty.front();
	empty.pop_front();
	int legalValueCounter = sdk.countLegalValues(var.first, var.second);

	//parcours les case non vide et conserve celle ayant le moins de valeurs possible
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

list<Pair> Agent::MinimumRemainingValues(Sudoku sdk) {

	list<Pair> empty = sdk.getEmptyCells();
	Pair var = empty.front();
	empty.pop_front();

	list<Pair> vars;
	vars.push_back(var);

	int legalValueCounter = sdk.countLegalValues(var.first, var.second);

	// parcours les cases non vide et conserve la liste de celles ayant le moins de valeurs possible
	while (!empty.empty()) {

		var = empty.front();
		empty.pop_front();

		int legalValueCounterExplored = sdk.countLegalValues(var.first, var.second);

		// réinitialise la liste si une valeur plus faible est trouvée
		if (legalValueCounterExplored < legalValueCounter) {
			legalValueCounter = legalValueCounterExplored;
			vars.clear();
		}

		// ajoute la case à la liste si le nombre de valeur possible est le plus faible
		if (legalValueCounterExplored == legalValueCounter) {
			vars.push_back(var);
		}
	}

	return vars;
}

Pair Agent::DegreeHeuristic(Sudoku sdk) {
	
	list<Pair> vars = MinimumRemainingValues(sdk);
	Pair var = vars.front();
	vars.pop_front();

	int constraintCounter = countConstraints(sdk);

	while (!vars.empty()) {

		Pair varExplored = vars.front();
		vars.pop_front();

		list<int> legalValues = sdk.getLegalValues(varExplored.first, varExplored.second);

		if (!legalValues.empty()) {

			// determine le nombre de contrainte à l'étape suivante
			Sudoku copy = sdk.copy();
			copy.set(varExplored.first, varExplored.second, legalValues.front());
			int constraintCounterExplored = countConstraints(copy);

			// conserve la case ayant le plus de contrainte
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
	int constraintCounter = 0;

	// parcours les case non vide et ajoute le nombre de contraintes
	while (!empty.empty()) {
		Pair var = empty.front();
		empty.pop_front();
		constraintCounter += 9 - sdk.countLegalValues(var.first, var.second);
	}

	return constraintCounter;
}

Sudoku Agent::backtrackingSearch(const Sudoku& sdk) {
	pair<Sudoku, bool> result = recursiveBacktrackingSearch(sdk);
	return result.first;
}

pair<Sudoku, bool> Agent::recursiveBacktrackingSearch(Sudoku sdk) {

	// test si la grille est valide
	list<Pair> empty = sdk.getEmptyCells();
	if (empty.empty()) return make_pair(sdk, true);

	// détermine la case à explorer
	Pair var = MinimumRemainingValue(sdk);
	//Pair var = DegreeHeuristic(sdk);

	list<int> legalValues = sdk.getLegalValues(var.first, var.second);

	// parcours les valeurs possible
	while (!legalValues.empty()) {
		
		int value = legalValues.front();
		legalValues.pop_front();

		Sudoku copy = sdk.copy();
		copy.set(var.first, var.second, value);
		
		pair<Sudoku, bool> result = recursiveBacktrackingSearch(copy);

		if (result.second){
            return result;
		}
	}
	return make_pair(sdk, false);
}

Pair Agent::LeastConstrainingValue(Sudoku sdk) {
    return Pair();
}
