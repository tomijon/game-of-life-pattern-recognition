#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Command {
public:
	Command(string name) : name(name) {}
	string getName() { return name; }
	void run() { try { execute(); } catch (...) { errorHandle(); } }

protected:
	virtual void execute() = 0;
	virtual void displayMessage(string input) { cout << input << " > "; }
	virtual void errorHandle() { throw runtime_error("Command failed."); }

	string name;
};


// Command class for getting input from the user.
class InputCommand : public Command {
public:
	InputCommand(string name) : Command(name) {}
	string getResult() { return result; }

protected:
	string getInput() {
		string input;
		cin >> input;
		return input;
	}

	void execute() override {
		displayMessage("Enter > ");
		result = getInput();
	}

	string result;
};


// Command class for getting an integer from the user.
class GetIntCommand : public InputCommand {
public:
	GetIntCommand(string name) : InputCommand(name) {}
	int getResult() { return result; }

protected:
	void execute() override {
		displayMessage("Enter an integer");
		result = getInt();
	}

	int getInt() {
		return stoi(getInput());
	}

	void errorHandle() override { cout << "ERROR: Input does not meet criteria." << endl; }

	int result;
};


// Command class for getting the grid width from the user.
class GetWidthCommand : private GetIntCommand {
public:
	GetWidthCommand() : GetIntCommand("width") {}
protected:
	void execute() override {
		displayMessage("Enter the width for the grid");
		result = getInt();

		if (result <= 0) throw runtime_error("Width cannot be 0 or less.");
	}
};


class GetHeightCommand : private GetIntCommand {
protected:
	void execute() override {
		displayMessage("Enter the height for the grid");
		result = getInt();

		if (result <= 0) throw runtime_error("Height cannot be 0 or less.");
	}
};


class GetStartingAliveCommand : private GetIntCommand {
protected:
	void execute() override {
		displayMessage("Enter the number of alive cells to start with");
		result = getInt();

		if (result < 0) throw runtime_error("Cannot start with less than 0 alive cells.");
	}
};


class GetNumberOfGenerations : private GetIntCommand {
protected:
	void execute() override {
		displayMessage("Enter how many generations should be run");
		result = getInt();

		if (result < 0) throw runtime_error("Cannot run for less than 0 generations.");
	}
};


class Menu {
public:
	void register_command(string name, Command command) { commandMap[name] = command; }

private:
	unordered_map<string, Command> commandMap;
};


class Question1 : public Menu {
public:
private:

};