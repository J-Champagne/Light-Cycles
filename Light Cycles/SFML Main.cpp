#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <typeinfo>

//My classes
#include "Cell Objects.h"
#include "GameArray.h"
using namespace std;

//Prototypes
void fillGameSpace();
void calcMovement(Bike* playerBike);
//End Prototypes

bool called = false;

int main()
{
	//Game space initialization and creation of bike objects
	fillGameSpace();

	Bike player1 = Bike("Player 1");
	Bike player2 = Bike(Position(37, 14), Left, Color::Blue, Color::Color(100, 100, 255), "Player 2");

	gameArray[player1.bikePos.x][player1.bikePos.y] = player1;
	gameArray[player2.bikePos.x][player2.bikePos.y] = player2;

	//Game clock variables
	Clock clock;
	float time = 0;

	//Create the render window
	RenderWindow window(VideoMode(802, 582), "Light Cycles");

	//End of the rendering of the background and base for graphics
	

	//Main game loop
	while (window.isOpen())
	{
		window.setFramerateLimit(60);

	

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			//Key Listening
			if (event.type == Event::KeyPressed)
			{

				if (event.key.code == Keyboard::W)
				{
					player1.setDirection(Up);
				}
				if (event.key.code == Keyboard::A)
				{
					player1.setDirection(Left);
				}
				if (event.key.code == Keyboard::S)
				{
					player1.setDirection(Down);
				}
				if (event.key.code == Keyboard::D)
				{
					player1.setDirection(Right);
				}

				if (event.key.code == Keyboard::Up)
				{
					player2.setDirection(Up);
				}
				if (event.key.code == Keyboard::Down)
				{
					player2.setDirection(Down);
				}
				if (event.key.code == Keyboard::Right)
				{
					player2.setDirection(Right);
				}
				if (event.key.code == Keyboard::Left)
				{
					player2.setDirection(Left);
				}
				
			}
		}

		//Physics
		if (player1.isAlive && player2.isAlive)
		{
			calcMovement(&player1);
			calcMovement(&player2);
		}
		
		

		window.clear();//All graphics must follow 

		if (!player1.isAlive || !player2.isAlive)
		{
			if (!player1.isAlive && !player2.isAlive)
			{
				RectangleShape rectEnd;
				rectEnd.setSize(Vector2f(805, 605));
				rectEnd.setFillColor(Color::Red);

				Font endFont;
				endFont.loadFromFile("font/font.ttf");

				Text textEnd;
				textEnd.setString("Both bikes died");
				textEnd.setFont(endFont);
				textEnd.setColor(Color::Black);
				textEnd.setCharacterSize(128);
				textEnd.setPosition(120, 150);

				window.draw(rectEnd);
				window.draw(textEnd);
			}
			if (player1.isAlive && !player2.isAlive)
			{
				RectangleShape rectEnd;
				rectEnd.setSize(Vector2f(805, 605));
				rectEnd.setFillColor(Color::Red);

				Font endFont;
				endFont.loadFromFile("font/font.ttf");

				Text textEnd;
				textEnd.setString("Game over\nBike 1 wins");
				textEnd.setFont(endFont);
				textEnd.setColor(Color::Black);
				textEnd.setCharacterSize(128);
				textEnd.setPosition(200, 150);

				window.draw(rectEnd);
				window.draw(textEnd);
			}
			if (!player1.isAlive && player2.isAlive)
			{
				RectangleShape rectEnd;
				rectEnd.setSize(Vector2f(805, 605));
				rectEnd.setFillColor(Color::Red);

				Font endFont;
				endFont.loadFromFile("font/font.ttf");

				Text textEnd;
				textEnd.setString("Game over\nBike 2 wins");
				textEnd.setFont(endFont);
				textEnd.setColor(Color::Black);
				textEnd.setCharacterSize(128);
				textEnd.setPosition(200, 150);

				window.draw(rectEnd);
				window.draw(textEnd);
			}
		}

		if (player1.isAlive && player2.isAlive) {
			for (int x = 0; x < 40; x++)
			{
				for (int y = 0; y < 29; y++)
				{
					RectangleShape cellShape;
					cellShape.setFillColor(gameArray[x][y].cellColor);
					cellShape.setPosition(Vector2f((20 * x) + 2, (20 * y) + 2));
					cellShape.setSize(Vector2f(18, 18));
					window.draw(cellShape);
				}
			}
		}

		window.display(); //End of all graphics

	}
}


void fillGameSpace(/*Cell gameSpaceArray[40][30]*/)
{
	for (int x = 0; x < 40; x++)
	{
		for (int y = 0; y < 39; y++)
		{
			if ((x == 0 || y == 0) || ( x == 39 || y == 28))
			{
				gameArray[x][y] = Wall();
			}
			else {
				gameArray[x][y] = Cell();
			}
		}
	}
}

void calcMovement(Bike* playerBike) //Method finds direction of the bike then moves the bike in the array accordingly.
{

	switch (playerBike->bikeDirection)
	{
	case Up:
		//TODO Ask P-Body if the syntax "gameArray[playerBike->bikePos.x++][playerBike->bikePos.y]" increments bikePos.x and makes the array index referenced one larger than the original bikePos.
		if (gameArray[playerBike->bikePos.x][playerBike->bikePos.y - 1].collideable) {
		playerBike->isAlive = false;
		}
		else {
			gameArray[playerBike->bikePos.x][playerBike->bikePos.y - 1] = *playerBike;
			playerBike->bikePos.y--;
			gameArray[playerBike->bikePos.x][playerBike->bikePos.y + 1] = Light(playerBike->bikeLightColor);
		}
		break;

	case Down:
		if (gameArray[playerBike->bikePos.x][playerBike->bikePos.y + 1].collideable) {
		playerBike->isAlive = false;
		}
		else {
			gameArray[playerBike->bikePos.x][playerBike->bikePos.y + 1] = *playerBike;
			playerBike->bikePos.y++;
			gameArray[playerBike->bikePos.x][playerBike->bikePos.y - 1] = Light(playerBike->bikeLightColor);
		}
		break;

	case Right:
		if (gameArray[playerBike->bikePos.x + 1][playerBike->bikePos.y].collideable) {
		playerBike->isAlive = false;
		}
		else {
			gameArray[playerBike->bikePos.x + 1][playerBike->bikePos.y] = *playerBike;
			playerBike->bikePos.x++;
			gameArray[playerBike->bikePos.x - 1][playerBike->bikePos.y] = Light(playerBike->bikeLightColor);
		}
		break;

	case Left:
		if (gameArray[playerBike->bikePos.x - 1][playerBike->bikePos.y].collideable) {
		playerBike->isAlive = false;
		}
		else {
			gameArray[playerBike->bikePos.x - 1][playerBike->bikePos.y] = *playerBike;
			playerBike->bikePos.x--;
			gameArray[playerBike->bikePos.x + 1][playerBike->bikePos.y] = Light(playerBike->bikeLightColor);
		}
		break;
	}
}