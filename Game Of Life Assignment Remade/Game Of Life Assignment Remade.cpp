#include "cell.hpp"

#include <iostream>
#include <thread>
#include <chrono>
#include <string>

using namespace GameOfLife;
using namespace Patterns;


void setWidth(World& world) {
	string width;
	cout << "Enter world width > ";
	cin >> width;
	world.setXRange(0, stoi(width));
}


void setPattern(World& world) {
	string patternName;
	cout << "Enter the name of pattern to search for: " << endl;
	cout << "Available Names:" << endl;
	for (string pattern : Base::names) {
		cout << "    - " << pattern << endl;
	}
	cout << " > ";
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
	cout << "Enter world height > ";
	cin >> height;
	world.setYRange(0, stoi(height));
}


void setInitialAlive(World& world) {
	string initialCount;
	cout << "Enter the number of starting alive cells > ";
	cin >> initialCount;
	world.setInitial(stoi(initialCount));
}


void setTargetGeneration(World& world) {
	string targetGen;
	cout << "Enter the maximum generation count > ";
	cin >> targetGen;
	world.setTargetGeneration(stoi(targetGen));
}


void setSeed(World& world) {
	string seed;
	cout << "Enter generator seed > ";
	cin >> seed;
	world.setSeed(stoi(seed));
}


string getYesNo() {
	string yesNo;
	cout << "Yes or No? > ";
	cin >> yesNo;
	for (int i = 0; i < yesNo.size(); i++) yesNo[i] = tolower(yesNo.at(i));
	return yesNo;
}


string getFileName() {
	string name;
	cout << "Enter file name > ";
	cin >> name;
	return name;
}


int main() {
	///*Pattern block = Pattern();

	//block.addCell(0, 0);
	//block.addCell(1, 0);
	//block.addCell(0, 1);
	//block.addCell(1, 1);
	//block.setOffset(0, 0);
	//block.setPeriod(1);*/

	//Pattern beehive = Pattern();
	//beehive.addCell(1, 0);
	//beehive.addCell(2, 0);
	//beehive.addCell(0, 1);
	//beehive.addCell(3, 1);
	//beehive.addCell(1, 2);
	//beehive.addCell(2, 2);
	//beehive.setPeriod(1);

	//Pattern glider = Pattern();
	//glider.addCell(0, 0);
	//glider.addCell(1, 1);
	//glider.addCell(2, 1);
	//glider.addCell(0, 2);
	//glider.addCell(1, 2);
	//glider.setPeriod(4);
	//glider.setOffset(-1, -1);

	//Pattern toad = Pattern();
	//toad.addCell(1, 0);
	//toad.addCell(0, 1);
	//toad.addCell(0, 2);
	//toad.addCell(3, 1);
	//toad.addCell(3, 2);
	//toad.addCell(2, 3);
	//toad.setPeriod(2);
	//toad.setOffset(0, 0);

	World world;

	cout << "Would you like to load a previous save?" << endl;
	string load = getYesNo();
	if (load == "yes") {
		world.load(getFileName());
		goto execute;
	}

	system("cls");

	cout << "GENERATING NEW SIMULATION" << endl;

	setWidth(world);
	setHeight(world);
	setInitialAlive(world);
	setTargetGeneration(world);
	setSeed(world);
	setPattern(world);

	int seed = world.getSee

execute:
	world.generate();
	cout << "Would you like to watch?" << endl;
	string watching = getYesNo();

	string autoPlay = "no";
	if (watching == "yes") {
		cout << "Would you like to autoplay?" << endl;
		autoPlay = getYesNo();
	}
	
	bool running = true;
	if (watching == "yes") {
		string output = world.toString();
		std::system("cls");
		std::cout << output;
	}

	while (not world.found()) {
		world.setSeed(rand());
		
		while (not world.found() and world.getGen() < world.getTargetGeneration()) {
			if (autoPlay == "no" and watching == "yes") {
				string x;
				cout << "Press 'Enter' to step forward.";
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
				cout << "Generation: " << world.getGen() << endl;
			}
		}
	}

	system("cls");
	std::cout << world.toString();

	if (world.found()) {
		cout << "PATTERN FOUND AT GENERATION " << world.getGen() << endl;
	}
	else {
		cout << "NO PATTERN FOUND" << endl;
	}

	if (load == "yes") return 0;
	cout << "Would you like to save?" << endl;
	string save = getYesNo();
	if (save == "yes") world.save(getFileName());

	return 0;
}