#include <iostream>
#include <array>
using namespace std;

struct cell{
    int num = 0;
    bool solved = false;
    int block = 0;
};

//defining Board as an array of cells.
using Board = array<array<cell,9>,9>;


//post: returns the block
array<cell,9> getBlock(Board& board, int i);

//post: returns true if an element in the board is already solved, returns false otherwise
bool SolveCell(Board& board,int& y, int& x);

//post: returns true if an element in the board is already empty, returns false otherwise
bool CanPlace(const Board& board, int y, int x, int number);

//post: prints the board
void Print(const Board& board);

//post: advances to next step
void increment(int& y, int& x, bool& solved);

//post: backtracks to previous step
void decrement(int& y, int& x);

//--------------------------------------------------------------------------------------------

array<cell,9> getBlock(const Board& board, int i){
    if(i < 1 || i > 9)
        return array<cell,9>();

    int j = 0;
    array<cell, 9> ret;
    for(int x = 0; x < 9; x++)
        for(int y = 0; y < 9; y++)
            if(board[y][x].block == i) {
                ret[j] = board[y][x];
                j++;
            }

    return ret;
}

bool SolveCell(Board& board, int& y, int& x){
    static bool solved = false;

    for (int number = 1; number < 10; number++){
        if (board[y][x].solved || CanPlace(board,y,x,number)){
            if(!board[y][x].solved)
                board[y][x].num = number;
            increment(y, x, solved);

            if(!solved)
                SolveCell(board, y, x);

            if(solved)
                return true;

            if(!board[y][x].solved)
                board[y][x].num = 0;

            decrement(y,x);

            if (board[y][x].solved)
                return false;
        }
    }

    if(!solved) {
        return false;
    }

    return true;
}

bool CanPlace(const Board& board, int y, int x, int number){
    array<cell,9> block = getBlock(board, board[y][x].block);

    for(const cell& c : block) {
        if (number == c.num) {
            return false;
        }
    }

    for(int x2 = 0; x2 < 9; x2++) {
        if (board[y][x2].num == number) {
            return false;
        }
    }

    for(int y2 = 0; y2 < 9; y2++) {
        if (board[y2][x].num == number) {
            return false;
        }
    }

    return true;
}

void Print(const Board& board){
    cout << "_____________________" << endl;
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            cout << board[j][i].num << " ";
            if(j == 8) {
                cout << endl;
            }
            if((j+1) % 3 == 0 && j!=8) {
                cout << "| ";
            }
        }
        if((i+1) % 3 == 0) {
            cout << "_____________________" << endl;
        }
    }
}

void increment(int& y, int& x, bool& solved){
    if(y == 8 && x == 8) {
        solved = true;
    }
    else {
        y++;
        if (y % 9 == 0) {
            y = 0;
            x++;
        }
    }
}

void decrement(int& y, int& x){
    if (y == 0) {
        x--;
        y = 8;
    }
    else y--;
}