#include <iostream>
using namespace std;

char board[3][3] = {
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'}
};

void displayBoard() {
    cout << "\n";
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << "\n";
    cout << "---|---|---\n";
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << "\n";
    cout << "---|---|---\n";
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << "\n";
    cout << "\n";
}

bool checkWin() {
    // Check rows and columns
    for(int i = 0; i < 3; i++) {
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return true;
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return true;
    }

    // Check diagonals
    if(board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return true;
    if(board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return true;

    return false;
}

bool checkDraw() {
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(board[i][j] != 'X' && board[i][j] != 'O')
                return false;
    return true;
}

int main() {
    int choice;
    char player = 'X';

    cout << "TIC TAC TOE GAME\n";

    while(true) {
        displayBoard();
        cout << "Player " << player << ", enter your choice (1-9): ";
        cin >> choice;

        int row = (choice - 1) / 3;
        int col = (choice - 1) % 3;

        if(choice < 1 || choice > 9 || 
           board[row][col] == 'X' || board[row][col] == 'O') {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        board[row][col] = player;

        if(checkWin()) {
            displayBoard();
            cout << "Player " << player << " wins!\n";
            break;
        }

        if(checkDraw()) {
            displayBoard();
            cout << "It's a draw!\n";
            break;
        }

        // Switch player
        player = (player == 'X') ? 'O' : 'X';
    }

    return 0;
}
