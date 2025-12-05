#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int puzzle[3][3];
int moves = 0;

// Display puzzle
void display() {
    cout << "\nMoves: " << moves << endl;
    cout << "-------------\n";
    for (int i = 0; i < 3; i++) {
        cout << "| ";
        for (int j = 0; j < 3; j++) {
            if (puzzle[i][j] == 0)
                cout << "  | ";
            else
                cout << puzzle[i][j] << " | ";
        }
        cout << "\n-------------\n";
    }
}

// Check solved
bool isSolved() {
    int val = 1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 2 && j == 2)
                return puzzle[i][j] == 0;
            if (puzzle[i][j] != val++)
                return false;
        }
    }
    return true;
}

// Find empty tile
void findZero(int &x, int &y) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (puzzle[i][j] == 0) {
                x = i;
                y = j;
                return;
            }
}

// Correct movement
void moveTile(char move) {
    int x, y;
    findZero(x, y);

    if (move == 'w' && x > 0)
        swap(puzzle[x][y], puzzle[x - 1][y]);
    else if (move == 's' && x < 2)
        swap(puzzle[x][y], puzzle[x + 1][y]);
    else if (move == 'a' && y > 0)
        swap(puzzle[x][y], puzzle[x][y - 1]);
    else if (move == 'd' && y < 2)
        swap(puzzle[x][y], puzzle[x][y + 1]);
    else {
        cout << "Invalid Move!\n";
        return;
    }

    moves++;
}

// Shuffle board
void shuffle() {
    int arr[9] = {0,1,2,3,4,5,6,7,8};
    srand(time(0));

    for (int i = 0; i < 9; i++) {
        int r = rand() % 9;
        swap(arr[i], arr[r]);
    }

    int k = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            puzzle[i][j] = arr[k++];
}

int main() {
    char ch;
    shuffle();

    cout << "===== NUMBER PUZZLE GAME =====\n";
    cout << "W = Up | S = Down | A = Left | D = Right\n";

    while (true) {
        display();

        if (isSolved()) {
            cout << "\n🎉 Puzzle Solved in " << moves << " moves!\n";
            break;
        }

        cout << "Enter move: ";
        cin >> ch;
        moveTile(tolower(ch));
    }

    return 0;
}
