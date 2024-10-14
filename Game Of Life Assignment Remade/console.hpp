#pragma once

#include <string>
#include <unordered_map>

using namespace std;

template <typename T>
class Command {
public:
	virtual void execute() = 0;
private:
	T returnValue;
};


class GetWidthCommand : public Command<int> {
public:
	void execute() override {

	}
private:
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