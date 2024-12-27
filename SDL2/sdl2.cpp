#include "/opt/homebrew/include/SDL2/SDL.h"

using namespace std;

int main() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawPoint(renderer, 320, 240);

    SDL_RenderPresent(renderer);
    
    bool quit = false;
    SDL_Event e;

    while( !quit )
    {
        while( SDL_PollEvent( &e ) != 0 ) 
        {
            if( e.type == SDL_QUIT ) 
            {
                quit = true;
            }
        }
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}