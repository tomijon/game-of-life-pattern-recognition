#include "cell.hpp"

#include <iostream>
#include <thread>
#include <chrono>
#include <string>

using namespace GameOfLife;
using namespace Patterns;




int ern(int width, int height, int active) {
	return width + height + active;
}


void setWidth(World& world) {
	string width;
	std::cout << "Enter world width > ";
	cin >> width;
	world.setXRange(0, stoi(width));
}


void setPattern(World& world) {
	string patternName;
	std::cout << "Enter the name of pattern to search for: " << endl;
	std::cout << "Available Names:" << endl;
	for (string pattern : Base::names) {
		std::cout << "    - " << pattern << endl;
	}
	std::cout << " > ";
	cin >> patternName;
	for (int i = 0; i < patternName.size(); i++) patternName[i] = tolower(patternName.at(i));
	for (int i = 0; i < 7; i++) {
		if (patternName == Base::names[i]) {
			world.searchFor(Base::BasePattern(1 << i));
			break;
		}
	}
}


void setHeight(World& world) {
	string height;
	std::cout << "Enter world height > ";
	cin >> height;
	world.setYRange(0, stoi(height));
}


void setInitialAlive(World& world) {
	string initialCount;
	std::cout << "Enter the number of starting alive cells > ";
	cin >> initialCount;
	world.setInitial(stoi(initialCount));
}


void setTargetGeneration(World& world) {
	string targetGen;
	std::cout << "Enter the maximum generation count > ";
	cin >> targetGen;
	world.setTargetGeneration(stoi(targetGen));
}


void setSeed(World& world) {
	string seed;
	std::cout << "Enter generator seed > ";
	cin >> seed;
	world.setSeed(stoi(seed));
}


string getYesNo() {
	string yesNo;
	std::cout << "Yes or No? > ";
	cin >> yesNo;
	for (int i = 0; i < yesNo.size(); i++) yesNo[i] = tolower(yesNo.at(i));
	return yesNo;
}


string getFileName() {
	string name;
	std::cout << "Enter file name > ";
	cin >> name;
	return name;
}


void calculateERN() {
	Base::BasePattern allTypes[6] = {
		Base::BasePattern::BLOCK,
		Base::BasePattern::BEEHIVE,
		Base::BasePattern::BLINKER,
		Base::BasePattern::TOAD,
		Base::BasePattern::GLIDER,
		Base::BasePattern::LWSS
	};

	int index = 1;
	for (Base::BasePattern target : allTypes) {
		int width = 1;
		int height = 1;
		int x = 0;
		int y = 0;
		int active = 1;
		bool found = false;
		int result = 0;

		while (found == false) {
			//cout << "width " << width << endl;
			//cout << "height " << height << endl;
			//cout << "active " << active << endl;
			//cout << "found " << found << endl;
		
			World world;
			world.searchFor(target);
			world.setXRange(0, width);
			world.setYRange(0, height);

			for (int i = 0; i < active; i++) {
				x = i % width;
				y = i / width;
				//cout << x << ", " << y << endl;
				world.setAliveCell({ x, y });
			}

			world.createNeighbors();
			world.assignRegions();
			world.assignSections();

			vector<Region> regions = world.makeRegions();
			vector<Region> sections = world.makeSections();
			world.addToHistory(regions);
			world.addToHistory(sections);
			world.checkHistory(regions);
			world.checkHistory(sections);
			for (int i = 0; i < 1000; i++) {
				world.update();
			}

			if (world.hasHistory()) {
				found = true;
				result = ern(width, height, active);
				break;
			}

			active++;

			if (active > width * height) {
				if (width == height) width++;
				else height++;
			}

		}

		std::cout << Base::names[index] << " ern -> " << result << endl;
		index++;

		
	}
}


int main() {
	World world;

	std::cout << "Would you like to calculate ERNs?" << endl;
	string ern = getYesNo();

	if (ern == "yes") {
		calculateERN();
		return 0;
	}
	else system("cls");

	string cont = "no";

	std::cout << "Would you like to load a previous save?" << endl;
	string load = getYesNo();
	if (load == "yes") {
		world.load(getFileName());
		goto execute;
	}

	system("cls");

	std::cout << "GENERATING NEW SIMULATION" << endl;

	setWidth(world);
	setHeight(world);
	setInitialAlive(world);
	setTargetGeneration(world);
	setSeed(world);
	setPattern(world);

execute:
	world.generate();
	std::cout << "Would you like to watch?" << endl;
	string watching = getYesNo();

	string autoPlay = "no";
	if (watching == "yes") {
		std::cout << "Would you like to autoplay?" << endl;
		autoPlay = getYesNo();
	}
	
	bool running = true;
	if (watching == "yes") {
		string output = world.toString();
		std::system("cls");
		std::cout << output;
	}

	int initSeed = world.getSeed();

	while (not world.found()) {
		if (load == "no") {
			world.setSeed(world.getSeed() + 1);
			world.clearCells();
			world.generate();
		}

		while (not world.found() and world.getGen() < world.getTargetGeneration()) {
extend:
			if (autoPlay == "no" and watching == "yes") {
				string x;
				std::cout << "Press 'Enter' to step forward.";
				getline(cin, x);
			}
			else if (autoPlay == "yes" and watching == "yes") {
				this_thread::sleep_for(chrono::milliseconds(100));
			}

			world.update();

			if (watching == "yes") {
				string output = world.toString();
				std::system("cls");
				std::cout << output;
				std::cout << "Generation: " << world.getGen() << endl;
			}

		}
	}


	if (cont == "no") {
		system("cls");
		std::cout << world.toString();


		if (world.found()) {
			std::cout << "PATTERN FOUND AT GENERATION " << world.getGen() << endl;
			std::cout << "Found after " << world.getSeed() - initSeed << " experiments." << endl;
		}
		else {
			std::cout << "NO PATTERN FOUND" << endl;
		}

		std::cout << "Would you like to continue?" << endl;
		cont = getYesNo();
	}
	if (cont == "yes") {
		string line;
		getline(cin, line);
		while (line != "exit") {
			goto extend;
		}
	}

	if (load == "yes") return 0;
	std::cout << "Would you like to save?" << endl;
	string save = getYesNo();
	if (save == "yes") world.save(getFileName());

	return 0;
}