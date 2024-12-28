#include "Tictactoe.hpp"

int numVacant = 9;

std::vector<std::vector<char>> tttBoard {
    {'_', '_', '_'},
    {'_', '_', '_'},
    {'_', '_', '_'}
};

std::vector<Line> grid;
std::vector<Move> circles;
std::vector<Move> xs;

void drawX(SDL_Renderer* renderer, int x, int y, int length) {
    SDL_RenderDrawLine(renderer,
                       x - length/2, y - length/2, 
                       x + length/2, y + length/2);
    SDL_RenderDrawLine(renderer,
                       x + length/2, y - length/2, 
                       x - length/2, y + length/2);
}

void drawCircle(SDL_Renderer* renderer, int x, int y, int radius) {
    const int sides = 50;
    for(int i = 0; i < sides; i++) {
        float theta1 = (2 * M_PI * i) / sides;
        float theta2 = (2 * M_PI * (i + 1)) / sides;

        float x1 = x + radius * std::sin(theta1);
        float y1 = y + radius * std::cos(theta1);
        float x2 = x + radius * std::sin(theta2);
        float y2 = y + radius * std::cos(theta2);

        SDL_RenderDrawLine(renderer, (int)x1, (int)y1, (int)x2, (int)y2);
    }
}

Move determineQuadrant(float x, float y) {
    tttBoard[(int)(y / 240)][(int)(x / 240)] = 'o';
    numVacant--;
    return {
        120 + 240 * ((int)(x / 240)),
        120 + 240 * ((int)(y / 240))
    };
}

char determineWinner() {
    char winner = '/';

    // horizontal
    for(int i = 0; i < 3; i++) {
        if(tttBoard[i][0] == tttBoard[i][1] &&
           tttBoard[i][0] == tttBoard[i][2] &&
           tttBoard[i][0] != '_') {
            winner = tttBoard[i][0];
        }
    }

    // vertical
    for(int i = 0; i < 3; i++) {
        if(tttBoard[0][i] == tttBoard[1][i] &&
           tttBoard[0][i] == tttBoard[2][i] &&
           tttBoard[0][i] != '_') {
            winner = tttBoard[0][i];
        }
    }

    // diagonal
    if(tttBoard[0][0] == tttBoard[1][1] && 
       tttBoard[0][0] == tttBoard[2][2] && 
       tttBoard[0][0] != '_') {
        winner = tttBoard[0][0];
    } 
    else if(tttBoard[0][2] == tttBoard[1][1] && 
            tttBoard[0][2] == tttBoard[2][0] && 
            tttBoard[0][2] != '_') {
        winner = tttBoard[0][2];
    }

    // tie
    if(winner == '/' && numVacant == 0) {
        winner = 't';
    }

    return winner;
}

int minmaxAlg(bool isMaximizing) {
    char winner = determineWinner();
    if(winner != '/') {
        if(winner == 'x') return 10 + numVacant;
        else if(winner == 'o') return -10 - numVacant;
        else return 0; 
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
                    bestScore = std::max(bestScore, currScore);
                }
            }
        }
        return bestScore;
    } 
    else {
        int bestScore = INT_MAX;
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if (tttBoard[i][j] == '_') {
                    tttBoard[i][j] = 'o';
                    numVacant--;
                    int currScore = minmaxAlg(true);
                    tttBoard[i][j] = '_';
                    numVacant++;
                    bestScore = std::min(bestScore, currScore);
                }
            }
        }
        return bestScore;
    }
}

void computerMove() {
    int bestScore = INT_MIN;
    int coord[2] = {-1, -1};

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(tttBoard[i][j] == '_') {
                tttBoard[i][j] = 'x';
                numVacant--;
                int currScore = minmaxAlg(false);
                tttBoard[i][j] = '_';
                numVacant++;

                if(currScore > bestScore) {
                    bestScore = currScore;
                    coord[0] = i;
                    coord[1] = j;
                }
            }
        }
    }

    tttBoard[coord[0]][coord[1]] = 'x';
    xs.push_back({
        120 + 240 * coord[1], 
        120 + 240 * coord[0]
    });
    numVacant--;
}

void render(SDL_Renderer* renderer, 
            std::vector<Line> g, 
            std::vector<Move> cir, 
            std::vector<Move> xMoves) 
{
    for(const auto& l : g) {
        SDL_RenderDrawLine(renderer, l.x1, l.y1, l.x2, l.y2);
    }
    for(const auto& c : cir) {
        drawCircle(renderer, c.x, c.y, CRADIUS);
    }
    for(const auto& x : xMoves) {
        drawX(renderer, x.x, x.y, XLENGTH);
    }
    SDL_RenderPresent(renderer);
}
