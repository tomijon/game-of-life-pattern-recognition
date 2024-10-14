#include "cell.hpp"

#include <thread>
#include <chrono>

using namespace GameOfLife;

int main() {
	World world;
	world.setAliveCell({ 0, 0 });
	world.setAliveCell({ 1, 0 });
	world.setAliveCell({ 1, 1 });
	world.setAliveCell({ 0, 1 });

	world.setAliveCell({ 5, 5 });
	world.setAliveCell({ 5, 6 });
	world.setAliveCell({ 5, 7 });

	for (int i = 0; i < 100; i++) {
		int x = (rand() % 30);
		int y = (rand() % 30);
		world.setAliveCell({ x, y });
	}

	world.createNeighbors();
	
	int x = 0;

	while (true) {
		world.update();
		x++;

		if (x % 10000 == 0) cout << x << endl;
		//string output = world.toString(); 
		//std::system("cls");
		//std::cout << output;
	}


	return 0;
}