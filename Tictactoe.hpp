#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include "/opt/homebrew/include/SDL2/SDL.h"
#include <iostream>
#include <vector>
#include <climits>
#include <cmath>     

using namespace std;

#define XLENGTH 100
#define CRADIUS 50

// Structures
struct Line {
    int x1;
    int y1;
    int x2;
    int y2;
};

struct Move {
    int x;
    int y;
};

// Extern variables so they can be used in multiple .cpp files
extern int numVacant;
extern vector<std::vector<char>> tttBoard;
extern vector<Line> grid;
extern vector<Move> circles;
extern vector<Move> xs;

// Function prototypes
void drawX(SDL_Renderer* renderer, int x, int y, int length);
void drawCircle(SDL_Renderer* renderer, int x, int y, int radius);
Move determineQuadrant(float x, float y);
char determineWinner();
int minmaxAlg(bool isMaximizing);
void computerMove();
void render(SDL_Renderer* renderer, vector<Line> g, vector<Move> cir, vector<Move> xs);

#endif
