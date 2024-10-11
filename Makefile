all:
	g++ -I./include/ -L./lib/ -o main.exe ./src/*.cpp -O1 -Wall -Wno-missing-braces -lraylib -lopengl32 -lgdi32 -lwinmm
	g++ -I./include/ -L./lib/ -o main.out ./src/*.cpp -O1 -Wall -Wno-missing-braces -lraylib -lopengl32 -lgdi32 -lwinmm
	