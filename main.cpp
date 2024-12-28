#include "Tictactoe.hpp"

int main(int argc, char** argv) {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    grid.push_back({240, 0, 240, 720});
    grid.push_back({480, 0, 480, 720});
    grid.push_back({0, 240, 720, 240});
    grid.push_back({0, 480, 720, 480});

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(720, 720, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    render(renderer, grid, circles, xs);

    bool quit = false;
    SDL_Event e;

    while(!quit) {
        while(SDL_PollEvent(&e) != 0) {
            if(e.type == SDL_QUIT) {
                quit = true;
            }
            else if(e.type == SDL_MOUSEBUTTONUP) {
                circles.push_back(determineQuadrant(e.button.x, e.button.y));
                render(renderer, grid, circles, xs);

                if(determineWinner() != '/') {
                    std::cout << determineWinner() << '\n';
                    return 0;
                }

                SDL_Delay(1000);

                computerMove();
                render(renderer, grid, circles, xs);

                if(determineWinner() != '/') {
                    std::cout << determineWinner() << '\n';
                    return 0;
                }
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
