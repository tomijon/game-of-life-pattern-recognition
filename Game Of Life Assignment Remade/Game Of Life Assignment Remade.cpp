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

	for (int i = 0; i < 5000; i++) {
		int x = (rand() % 100);
		int y = (rand() % 50);
		world.setAliveCell({ x, y });
	}

	world.createNeighbors();
	

	while (true) {
		world.update();

		string x;

		//if (x % 1000 == 0) cout << x << endl;
		string output = world.toString(); 
		std::system("cls");
		std::cout << output;
		//getline(cin, x);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}


	return 0;
}