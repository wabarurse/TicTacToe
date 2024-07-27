//
//  main.cpp
//  TictactoeMinMax
//
//  Created by Richard Huang on 2024-07-26.
//

#include <iostream>
#include <vector>
#include <limits.h>


using namespace std;

int numVacant = 9;

vector<vector<char>> tttBoard {{'_', '_', '_'},
                               {'_', '_', '_'},
                               {'_', '_', '_'}};

//vector<vector<char>> tttBoard {{'o', '_', 'x'},
//                               {'o', 'o', '_'},
//                               {'x', '_', '_'}};


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

void printBoard() {
    for(auto vec : tttBoard) {
        for(auto v : vec) {
            cout << v << " ";
        }
        cout << '\n';
    }
    cout << '\n';
}


char determineWinner() {
    char winner = '/';
    
    // horizontal
    for(int i = 0; i < 3; i++) {
        if(tttBoard[i][0] == tttBoard[i][1] && tttBoard[i][0] == tttBoard[i][2] && tttBoard[i][0] != '_') {
            winner = tttBoard[i][0];
        }
    }
    
    // vertical
    for(int i = 0; i < 3; i++) {
        if(tttBoard[0][i] == tttBoard[1][i] && tttBoard[0][i] == tttBoard[2][i] && tttBoard[0][i] != '_') {
            winner = tttBoard[0][i];
        }
    }
    
    //diagonal
    if(tttBoard[0][0] == tttBoard[1][1] && tttBoard[0][0] == tttBoard[2][2] && tttBoard[0][0] != '_') {
        winner = tttBoard[0][0];
    } else if(tttBoard[0][2] == tttBoard[1][1] && tttBoard[0][2] == tttBoard[2][0] && tttBoard[0][2] != '_') {
        winner = tttBoard[0][2];
    }
    
    
    //tie
    if(winner == '/' && numVacant == 0) {
        winner = 't';
    }
    
    
    return winner;
    
}


int minmaxAlg(bool isMaximizing) {
    char winner = determineWinner();
    if(winner != '/') {
        if(winner == 'x') {
            return 10 + numVacant;
        } else if(winner == 'o') {
            return -10 - numVacant;
        } else {
            return 0;
        }
    }
    
    if(isMaximizing) {
        int bestScore = INT_MIN;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if (tttBoard[i][j] == '_') {
                    tttBoard[i][j] = 'x';
                    numVacant--;
                    int currScore = minmaxAlg(false);
                    tttBoard[i][j] = '_';
                    numVacant++;
                    bestScore = max(currScore, bestScore);
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = INT_MAX;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if (tttBoard[i][j] == '_') {
                    tttBoard[i][j] = 'o';
                    numVacant--;
                    int currScore = minmaxAlg(true);
                    tttBoard[i][j] = '_';
                    numVacant++;
                    bestScore = min(currScore, bestScore);
                }
            }
        }
        return bestScore;
    }
}


void computerMove() {
    int bestScore = INT_MIN;
    int coord[2] = {-1,-1};
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tttBoard[i][j] == '_') {
                tttBoard[i][j] = 'x';
                numVacant--;
                int currScore = minmaxAlg(false);
                tttBoard[i][j] = '_';
                numVacant++;

                if (currScore > bestScore) {
                    bestScore = currScore;
                    coord[0] = i;
                    coord[1] = j;
                }

            }
        }
    }
    
    tttBoard[coord[0]][coord[1]] = 'x';
    numVacant--;
    
}



int main() {
 
    char winner;

    while(true) {

        printBoard();
        playerMove();
        cout << "player move:" << '\n';

        winner = determineWinner();
        if(winner != '/') {
            printBoard();
            cout << winner << '\n';
            break;
        }

        printBoard();
        computerMove();
        cout << "computer move:" << '\n';


        winner = determineWinner();
        if(winner != '/') {
            printBoard();
            cout << winner << '\n';
            break;
        }

    }
    
}
