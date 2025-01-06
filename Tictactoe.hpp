#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

#include "/opt/homebrew/include/SDL2/SDL.h"
#include "/opt/homebrew/include/SDL2/SDL_ttf.h"
#include <iostream>
#include <vector>
#include <climits>
#include <cmath>  
#include <string>

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
    static Move invalid() {
        return {-1, -1};
    }
    bool isValid() {
        return x != -1 || y != -1;
    }
};

struct Button {
    SDL_Rect buttonRect;
};

struct Text {
    string text;
    int fontSize;
    int x;
    int y;
};

// Extern variables so they can be used in multiple .cpp files
extern int numVacant;
extern vector<vector<char>> tttBoard;
extern vector<Line> grid;
extern vector<Move> circles;
extern vector<Move> xs;
extern vector<Button> buttons;
extern vector<Text> texts;
extern TTF_Font* font;
extern int wlt[3];

void loadBackground(SDL_Window* window, SDL_Renderer* renderer);
void drawX(SDL_Renderer* renderer, int x, int y, int length);
void drawCircle(SDL_Renderer* renderer, int x, int y, int radius);
void drawButton(SDL_Renderer* renderer, Button b);
void drawText(SDL_Renderer* renderer, int fontSize, Text text);
void createText(string text, int fontSize, int x, int y);

void addWLT(string& str);
Move determineQuadrant(float x, float y);
char determineWinner();
int minmaxAlg(bool isMaximizing);
void playerMove();
void computerMove();
void render(SDL_Renderer* renderer, vector<Line> g, vector<Move> cir, vector<Move> xs, vector<Button> buttons, vector<Text> texts);
void clearBoard(SDL_Renderer* renderer);
bool gameEnd(SDL_Renderer* renderer, char winner);
void createButton(int x, int y, int length, int width);
bool isClicked(SDL_Rect rect, int mouseX, int mouseY);

#endif
