#include <iostream>
#include "sudoku.hpp"
using namespace std;

int main() {
    Board sudoku;

    {
        int tempSudoku[9][9] = {
                {0,2,0,6,0,8,0,0,0},
                {5,8,0,0,0,9,7,0,0},
                {0,0,0,0,4,0,0,0,0},
                {3,7,0,0,0,0,5,0,0},
                {6,0,0,0,0,0,0,0,4},
                {0,0,8,0,0,0,6,1,3},
                {0,0,0,0,2,0,0,0,0},
                {0,0,9,8,0,0,0,3,6},
                {0,0,0,3,0,6,0,9,0}
        };

        // inputting the board into a Board object.

        int index = 0;
        for(int x = 0; x < 9; x++) {
            if(x % 3 != 0 && index != 0)
                index -= 3;
            for(int y = 0; y < 9; y++) {
                if (y % 3 == 0) index++;
                sudoku[y][x].num = tempSudoku[x][y];
                sudoku[y][x].block = index;
                if(tempSudoku[x][y] != 0)
                    sudoku[y][x].solved = true;
            }
        }
    }

    Print(sudoku);
    int y = 0, x = 0;
    cout << (SolveCell(sudoku,y,x) ? "\nHere is your solved table!\n" : "\nNot a valid table\n") <<endl;
    Print(sudoku);
    return 0;
}
