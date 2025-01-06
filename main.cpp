#include "Tictactoe.hpp"

int main(int argc, char** argv) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_CreateWindowAndRenderer(720, 840, 0, &window, &renderer);

    SDL_StartTextInput();
    texts.push_back({"you : 0", 24, 0, 720});
    texts.push_back({"computer : 0", 24, 0, 760});
    texts.push_back({"tie : 0", 24, 0, 800});

    bool gameOver = false;

    while (!gameOver) {
        grid.push_back({240, 0, 240, 720});
        grid.push_back({480, 0, 480, 720});
        grid.push_back({0, 240, 720, 240});
        grid.push_back({0, 480, 720, 480});
        grid.push_back({0, 720, 720, 720});
        
        render(renderer, grid, circles, xs, buttons, texts);


        bool quit = false;
        SDL_Event e;

        while(!quit) {
            while(SDL_PollEvent(&e) != 0) {
                
                if(e.type == SDL_QUIT) {
                    quit = true;
                } else {
                    playerMove();

                    render(renderer, grid, circles, xs, buttons, texts);

                    if(determineWinner() != '/') {
                        if(gameEnd(renderer, determineWinner())) {
                            cout << "first" << '\n';
                            SDL_DestroyRenderer(renderer);
                            SDL_DestroyWindow(window);
                            SDL_Quit();
                            return 0;
                        } else {
                            clearBoard(renderer);
                        }
                    }

                    SDL_Delay(1000);

                    computerMove();
                    render(renderer, grid, circles, xs, buttons, texts);

                    if(determineWinner() != '/') {
                        if(gameEnd(renderer, determineWinner())) {
                            cout << "second" << '\n';
                            SDL_DestroyRenderer(renderer);
                            SDL_DestroyWindow(window);
                            SDL_Quit();
                            return 0;
                        } else {
                            clearBoard(renderer);
                        }
                    }
                }
                SDL_Delay(10);
            }
        }

    }
    
    
}
