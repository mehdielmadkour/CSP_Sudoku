#include "Sudoku.h"
#include "Agent.h"
using namespace std;

int main()
{
	cout << "Fichier Simple Sudoku : ";
	string file;
	cin >> file;
	Sudoku sudoku = Sudoku(file);
	Agent agent = Agent(sudoku);
	return 0;
}
