#include "Tictactoe.hpp"

int numVacant = 9;

vector<vector<char>> tttBoard {
    {'_', '_', '_'},
    {'_', '_', '_'},
    {'_', '_', '_'}
};

vector<Line> grid;
vector<Move> circles;
vector<Move> xs;
vector<Button> buttons;
vector<Text> texts;

void loadBackground(SDL_Window* window, SDL_Renderer* renderer) {

}

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

        float x1 = x + radius * sin(theta1);
        float y1 = y + radius * cos(theta1);
        float x2 = x + radius * sin(theta2);
        float y2 = y + radius * cos(theta2);

        SDL_RenderDrawLine(renderer, (int)x1, (int)y1, (int)x2, (int)y2);
    }
}

void drawButton(SDL_Renderer* renderer, Button b) {
    SDL_RenderDrawRect(renderer, &b.buttonRect);
}

void drawText(SDL_Renderer* renderer, Text text) {
    SDL_Surface* surface = TTF_RenderText_Solid(TTF_OpenFont("OpenSans-Regular.ttf", text.fontSize), text.text.c_str(), {255, 255, 255});
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect dstRect = {text.x, text.y, surface->w, surface->h};
    
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect); 

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void addWLT(string& str) {
    for (int i = 0; i < str.length(); i++) {
        if (isdigit(str[i])) {
            int start = i;
            while (i < str.size() && isdigit(str[i])) i++;
            int number = stoi(str.substr(start, i - start)) + 1;
            str.replace(start, i - start, to_string(number));
            return;
        }
    }
}

Move determineQuadrant(float x, float y) {
    int r = (int)(y / 240);
    int c = (int)(x / 240);
    if(r > 2 || c > 2 || tttBoard[r][c] != '_') {
        return Move::invalid();
    }
    tttBoard[(int)(y / 240)][(int)(x / 240)] = 'o';
    numVacant--;
    return {
        120 + 240 * ((int)(x / 240)),
        120 + 240 * ((int)(y / 240))
    };
}

void playerMove() {
    while (true) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_MOUSEBUTTONUP) {
                Move move = determineQuadrant(event.button.x, event.button.y);

                if (move.isValid()) {
                    circles.push_back(move);
                    return; 
                } else {
                    cout << "Error: invalid move, please try again.\n";
                }
            }
        }
    }
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
                    bestScore = max(bestScore, currScore);
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
                    bestScore = min(bestScore, currScore);
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

void createButton(int x, int y, int length, int width) {
    buttons.push_back({x, y, length, width});
}

bool isClicked(SDL_Rect rect, int mouseX, int mouseY) {
    return mouseX > rect.x && mouseX < rect.x + rect.w && mouseY > rect.y && mouseY < rect.y + rect.h;
}

void createText(string text, int fontSize, int x, int y) {
    texts.push_back({text, fontSize, x, y});
}

void render(SDL_Renderer* renderer, vector<Line> g, vector<Move> cir, vector<Move> xMoves, vector<Button> buttons, vector<Text> texts) {
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    
    for(const auto& l : g) {
        SDL_RenderDrawLine(renderer, l.x1, l.y1, l.x2, l.y2);
    }
    for(const auto& c : cir) {
        drawCircle(renderer, c.x, c.y, CRADIUS);
    }
    for(const auto& x : xMoves) {
        drawX(renderer, x.x, x.y, XLENGTH);
    }
    for(const auto& b : buttons) {
        drawButton(renderer, b);
    }
    for(const auto& t : texts) {
        drawText(renderer, t);
    }

    SDL_RenderPresent(renderer);
}

void clearBoard(SDL_Renderer* renderer) {
    grid.clear();
    circles.clear();
    xs.clear();
    render(renderer, grid, circles, xs, buttons, texts);
}

bool gameEnd(SDL_Renderer* renderer, char winner) {
    if(winner == 'o') {
        addWLT(texts[0].text);
        createText("YOU WON! (they should never see this)", 24, 240, 740);
    } else if(winner == 'x') {
        addWLT(texts[1].text);
        createText("YOU LOST! damn, you suck", 24, 240, 740);
    } else if(winner == 't') {
        addWLT(texts[2].text);
        createText("its a tie...", 24, 240, 740);
    }

    createButton(620, 720, 100, 60);
    createButton(620, 780, 100, 60);

    render(renderer, grid, circles, xs, buttons, texts);

    // chat gpt ----------

    bool running = true;
    bool gameEnd = false;

    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        int mouseX, mouseY;
        Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);

        if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT) && isClicked(buttons[0].buttonRect, mouseX, mouseY)) {
            running = false;
        }
        if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT) && isClicked(buttons[1].buttonRect, mouseX, mouseY)) {
            running = false;
            gameEnd = true;
        }

        SDL_Delay(10); 
    }
    cout << gameEnd << '\n';
    return gameEnd;
}

