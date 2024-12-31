all: 
	g++ -std=c++11 Button.cpp Tictactoe.cpp main.cpp -o out -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2

r:
	./out