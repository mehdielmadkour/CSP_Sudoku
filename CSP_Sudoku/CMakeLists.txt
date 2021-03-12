# CMakeList.txt : projet CMake pour CSP_Sudoku, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

# Ajoutez une source à l'exécutable de ce projet.
add_executable (CSP_Sudoku "CSP_Sudoku.cpp"  "Sudoku.cpp" "Sudoku.h" "Agent.h" "Agent.cpp")

# TODO: Ajoutez des tests et installez des cibles si nécessaire.
