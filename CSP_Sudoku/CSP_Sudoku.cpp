#include "Sudoku.h"
#include "Agent.h"
using namespace std;

int main()
{
	if (__cplusplus == 201703L) std::cout << "C++17\n";
	else if (__cplusplus == 201402L) std::cout << "C++14\n";
	else if (__cplusplus == 201103L) std::cout << "C++11\n";
	else if (__cplusplus == 199711L) std::cout << "C++98\n";
	else std::cout << "pre-standard C++\n";
	cout << "Fichier Simple Sudoku : ";
	string file;
	cin >> file;
	Sudoku sudoku = Sudoku(file);
	Agent agent = Agent(sudoku);
	return 0;
}
