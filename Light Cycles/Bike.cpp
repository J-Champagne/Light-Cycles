#include "Bike.h"
#include <iostream>

Bike::Bike() : Bike::Bike(Position(2, 14), Right, Color::Red, Color::Color(255, 100, 48, 255), "Default Player") {};

Bike::Bike(String name) : Bike::Bike(Position(2, 14), Right, Color::Red, Color::Color(255, 100, 48, 255), name) {};

Bike::Bike(Position initPosition, Direction initDirection, Color bikeColor, Color lightColor, String name)
{
	isAlive = true;
	collideable = true;
	cellColor = bikeColor;
	bikeDirection = initDirection;
	bikePos = initPosition;
	bikeLightColor = lightColor;
	bikeName = name;
}

void Bike::setDirection(Direction dir)
{
	bikeDirection = dir;
}