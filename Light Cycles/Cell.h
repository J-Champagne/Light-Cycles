#pragma once
#include <SFML\Graphics.hpp>

using namespace sf;

class Cell {

public:
	//Contructors
	Cell();

	//Variables
	Color cellColor;
	bool collideable;
};