#include "Agent.h"

Agent::Agent(Sudoku sudoku): sudoku(sudoku) {

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

		// r�initialise la liste si une valeur plus faible est trouv�e
		if (legalValueCounterExplored < legalValueCounter) {
			legalValueCounter = legalValueCounterExplored;
			vars.clear();
		}

		// ajoute la case � la liste si le nombre de valeur possible est le plus faible
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
	// Tant que la liste des cases vides avec le moins de valeurs l�gales n'est pas vide
	while (!vars.empty()) {

		Pair varExplored = vars.front();
		vars.pop_front();

		list<int> legalValues = sdk.getLegalValues(varExplored.first, varExplored.second);

		if (!legalValues.empty()) {

			// determine le nombre de contrainte � l'�tape suivante
			Sudoku copy = sdk;
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

int Agent::LeastConstrainingValue(Sudoku sdk,Pair var) 
{
	//Nombre de voisins maximale qui poss�de la m�me valeur l�gale que la case (var.first, var.second)
	int counter = 16;
	//Valeur � renvoy� (initialement � -1 comme pour une case vide)
	int value = -1;
	//Liste de tous les voisins
	list<Pair> neighbors;
	//Liste des cases voisines vides
	list<Pair> consideredNeighbors;
	//Liste des valeurs l�gales de la case (var.first, var.second)
	list<int> legalValues = sdk.getLegalValues(var.first, var.second);

	//r�cup�re la liste des voisins (ligne, colonne) de la case de coordonn�e var
	for (int i = 0; i < 9; i++) 
	{
		//r�cup�re la ligne des voisins
		if (i != var.first) 
		{
			neighbors.emplace_back(i, var.second);
		}
		//r�cup�re la colonne des voisins
		if (i != var.second) 
		{
			neighbors.emplace_back(var.first, i);
		}
	}
	//Pour chaque voisin check s'il est vide
	while(!neighbors.empty())
	{
		Pair p = neighbors.front();
		neighbors.pop_front();
	
		//retire les voisins non vide
		if (sdk.get(p.first, p.second) == -1) 
		{
			consideredNeighbors.push_back(p);
		}
	}
	//Pour chaque valeur l�gale pour la pair en argument de la question
	while(!legalValues.empty()) {
		int v = legalValues.front();
		legalValues.pop_front();
		int tmpcounter = 0;
		list<Pair> copyNeighbors = consideredNeighbors;
		//V�rification pour chaque voisin
		while(!copyNeighbors.empty())
		{
			Pair tmp = copyNeighbors.front();
			copyNeighbors.pop_front();
			list<int> tmpLegalValues = sdk.getLegalValues(tmp.first, tmp.second);
			//Comparaison avec chaque valeur l�gale du voisin
			while (!tmpLegalValues.empty())
			{
				int c = tmpLegalValues.front();
				tmpLegalValues.pop_front();
				if (c == v) {
					tmpcounter++;
				}
			}
		}
		//Si la valeur v est moins contraigante pour les voisins elle est retenue
		if (tmpcounter < counter) {
			counter = tmpcounter;
			//La valeur � retourner est mise � jour � chaque fois qu'on tombe sur une valeur l�gale moins contraignante
			value = v;
		}
	}
	return value;
}

Sudoku Agent::backtrackingSearch(const Sudoku& sdk) {
	pair<Sudoku, bool> result = recursiveBacktracking(sdk);
	return result.first;
}

pair<Sudoku, bool> Agent::recursiveBacktracking(Sudoku sdk) {

	// test si la grille est valide
	list<Pair> empty = sdk.getEmptyCells();
	if (empty.empty()) return make_pair(sdk, true);

	// d�termine la case � explorer
	Pair var = MinimumRemainingValue(sdk);
	//Pair var = DegreeHeuristic(sdk);

	list<int> legalValues = sdk.getLegalValues(var.first, var.second);

	// parcours les valeurs possible
	while (!legalValues.empty()) {
		
		int value = legalValues.front();
		legalValues.pop_front();

		Sudoku copy = sdk;
		copy.set(var.first, var.second, value);
		
		pair<Sudoku, bool> result = recursiveBacktracking(copy);

		if (result.second){
            return result;
		}
	}
	return make_pair(sdk, false);
}

