#include "Button.hpp"
#include "Tictactoe.hpp"

Button::Button(int x, int y, int length, int width) {
    this->x = x;
    this->y = y;
    this->length = length;
    this->width = width;
}

void Button::createButton(SDL_Renderer* renderer) {
    SDL_Rect rect = {x, y, length, width};
    SDL_RenderDrawRect(renderer, &rect);
}

bool Button::isClicked(int mouseX, int mouseY) {

    return mouseX > x && mouseX < x + length && mouseY > y && mouseY < y + width;

}