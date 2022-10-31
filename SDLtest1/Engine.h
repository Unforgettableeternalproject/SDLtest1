#pragma once

#include "State.h"

class Engine
{
private:
	std::stack<State*> states;

	//Private functions
	void initStates();

public:
	//Constructors & Destructors
	Engine();
	~Engine();

	//Accessors

	//Modifiers

	//Functions
	void update();
	void render();
	void run();
};

