//
//  main.cpp
//  TictactoeMinMax
//
//  Created by Richard Huang on 2024-07-26.
//

#include <iostream>
#include <vector>

using namespace std;

int numVacant = 9;

vector<vector<char>> tttBoard {{'_', '_', '_'},
                               {'_', '_', '_'},
                               {'_', '_', '_'}};
void playerMove() {
    int choice;
    cout << "> ";
    cin >> choice;
    
    switch (choice) {
        case 1:
            tttBoard[0][0] = 'o';
            break;
        case 2:
            tttBoard[0][1] = 'o';
            break;
        case 3:
            tttBoard[0][2] = 'o';
            break;
        case 4:
            tttBoard[1][0] = 'o';
            break;
        case 5:
            tttBoard[1][1] = 'o';
            break;
        case 6:
            tttBoard[1][2] = 'o';
            break;
        case 7:
            tttBoard[2][0] = 'o';
            break;
        case 8:
            tttBoard[2][1] = 'o';
            break;
        default:
            tttBoard[2][2] = 'o';

    }
    
    numVacant--;
    
}

void printBoard(vector<vector<char>> board) {
    for(auto vec : board) {
        for(auto v : vec) {
            cout << v << " ";
        }
        cout << '\n';
    }
}


char determineWinner(vector<vector<char>> board) {
    char winner = '/';
    
    // horizontal
    for(int i = 0; i < 3; i++) {
        if(board[i][0] == board[i][1] && board[i][0] == board[i][2] && board[i][0] != '_') {
            winner = board[i][0];
        }
    }
    
    // vertical
    for(int i = 0; i < 3; i++) {
        if(board[0][i] == board[1][i] && board[0][i] == board[2][i] && board[0][i] != '_') {
            winner = board[0][i];
        }
    }
    
    //diagonal
    if(board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != '_') {
        winner = board[0][0];
    } else if(board[0][2] == board[1][1] && board[0][0] == board[2][0] && board[0][2] != '_') {
        winner = board[0][2];
    }
    
    
    //tie
    if(winner == '/' && numVacant == 0) {
        winner = 't';
    }
    
    
    return winner;
    
}


int minmaxAlg(vector<vector<char>> board, bool isMaximizing) {
    char winner = determineWinner(tttBoard);
    int score;
    if(winner != '/') {
        if(winner == 'x') {
            score = 1 + 1 * numVacant;
        } else if(winner == 'o') {
            score = -1 - 1 * numVacant;
        } else {
            score = 0;
        }
        return score;
    }
    
    if(isMaximizing) {
        int bestScore = -100;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'x';
                    int currScore = minmaxAlg(board, false);
                    board[i][j] = ' ';
                    bestScore = max(currScore, bestScore);
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 100;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'x';
                    int currScore = minmaxAlg(board, true);
                    board[i][j] = ' ';
                    bestScore = min(currScore, bestScore);
                }
            }
        }
        return bestScore;
    }
}


void computerMove() {
    int bestScore = -100;
    int coord[2];
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tttBoard[i][j] == ' ') {
                tttBoard[i][j] = 'X';
                int score = minmaxAlg(tttBoard, false);
                tttBoard[i][j] = ' ';

                if (score > bestScore) {
                    bestScore = score;
                    coord[0] = i;
                    coord[1] = j;
                }

            }
        }
    }
    
}



int main() {
    printBoard(tttBoard);
    playerMove();
    printBoard(tttBoard);
}
