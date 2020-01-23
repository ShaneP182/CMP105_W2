#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include <string.h>
#include <iostream>


class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in);
	~Level();

	void handleInput();
	void update();
	void render();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;

	// Add your object here

	// objects/variables for mouse position
	sf::Font font;
	sf::Text mousePosDisplay;
	std::string mousePos;

	// variables for calculating distance of mouse drag
	sf::Vector2i initialPos;
	sf::Vector2i finalPos;
	float distance;
	float xDif;
	float yDif;
	bool mouseClicked = false;

	// circle object to be rendered on mouse click
	sf::CircleShape circle;

};