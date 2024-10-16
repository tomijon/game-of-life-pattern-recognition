#include "pattern.hpp"
#include "cell.hpp"

#include <thread>
#include <chrono>

using namespace GameOfLife;
using namespace Patterns;

int main() {
	/*Pattern block = Pattern();

	block.addCell(0, 0);
	block.addCell(1, 0);
	block.addCell(0, 1);
	block.addCell(1, 1);
	block.setOffset(0, 0);
	block.setPeriod(1);*/

	Pattern beehive = Pattern();
	beehive.addCell(1, 0);
	beehive.addCell(2, 0);
	beehive.addCell(0, 1);
	beehive.addCell(3, 1);
	beehive.addCell(1, 2);
	beehive.addCell(2, 2);
	beehive.setPeriod(1);

	Pattern glider = Pattern();
	glider.addCell(0, 0);
	glider.addCell(1, 1);
	glider.addCell(2, 1);
	glider.addCell(0, 2);
	glider.addCell(1, 2);
	glider.setPeriod(4);
	glider.setOffset(-1, -1);


	World world;
	/*world.setAliveCell({ 0, 0 });
	world.setAliveCell({ 1, 0 });
	world.setAliveCell({ 1, 1 });
	world.setAliveCell({ 0, 1 });

	world.setAliveCell({ 5, 5 });
	world.setAliveCell({ 5, 6 });
	world.setAliveCell({ 5, 7 });*/

	world.setSearchingPattern(glider);

	/*for (int i = 0; i < 90; i++) {
		int x = (rand() % 20);
		int y = (rand() % 20);
		world.setAliveCell({ x, y });
	}*/
	
	world.setAliveCell({ 5, 4 });
	world.setAliveCell({ 6, 4 });
	world.setAliveCell({ 5, 5 });
	world.setAliveCell({ 5, 6 });
	world.setAliveCell({ 4, 5 });

	world.createNeighbors();

	world.createNeighbors();
	world.assignRegions();
	vector<Patterns::Region> regions = world.makeRegions();
	world.addToHistory();
	world.gen++;

	
	bool running = true;
	string output = world.toString(); 
	std::system("cls");
	std::cout << output;

	while (running) {

		string x;
		getline(cin, x);

		world.update();
		//if (x % 1000 == 0) cout << x << endl;
		string output = world.toString(); 
		std::system("cls");
		std::cout << output;
		//std::this_thread::sleep_for(std::chrono::milliseconds(100));

		if (world.found()) {
			running = false;
		}
	}

	cout << "FOUND GLIDER AT GENERATION " << world.getGen() << endl;


	return 0;
}