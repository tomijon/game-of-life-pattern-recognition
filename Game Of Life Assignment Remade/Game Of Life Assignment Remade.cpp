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
	World world;
	string cont = "no";

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