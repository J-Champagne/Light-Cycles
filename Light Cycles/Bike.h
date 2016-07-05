#pragma once
#include <string>
#include "Cell.h"
#include "Direction.h"
#include "Position.h"
#include "GameArray.h"

class Bike : public Cell {
public:
	Bike();
	Bike(String name);
	Bike(Position initPosition, Direction initDirection, Color bikeColor, Color lightColor, String name);

	//Bike things
	String bikeName;
	bool isAlive;

	
	Position bikePos;
	Direction bikeDirection;
	Color bikeLightColor;

	//Methods for bike
	void setDirection(Direction dir);

};