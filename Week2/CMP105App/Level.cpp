#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects

	// load font and error check
	if (!font.loadFromFile("font/arial.ttf"))
	{
		std::cout << "Error loading font.";
	}

	// create text to display mouse position
	mousePosDisplay.setFont(font);
	mousePosDisplay.setFillColor(sf::Color::Red);
	mousePosDisplay.setCharacterSize(16);
	mousePosDisplay.setPosition(0, 0);

	// create red circle with radius 20
	circle.setFillColor(sf::Color::Red);
	circle.setRadius(20);
	
}

Level::~Level()
{
	input = nullptr;
}

// handle user input
void Level::handleInput()
{
	// Outputs to console when W key is pressed.
	if (input->isKeyDown(sf::Keyboard::W))
	{
		input->setKeyUp(sf::Keyboard::W);
		std::cout << "The 'W' key was pressed.\n";
	}

	// Outputs to console when J, K and L are pressed together.
	if (input->isKeyDown(sf::Keyboard::J) && input->isKeyDown(sf::Keyboard::K) && input->isKeyDown(sf::Keyboard::L))
	{
		input->setKeyUp(sf::Keyboard::J);
		input->setKeyUp(sf::Keyboard::K);
		input->setKeyUp(sf::Keyboard::L);
		std::cout << "Keys 'J', 'K', and 'L' were pressed simultaneously.\n";
	}

	// Closes application window when escape key is pressed.
	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		input->setKeyUp(sf::Keyboard::Escape);
		window->close();
	}

	// For calculating difference between mouse click and release
	if (input->isMouseLDown())
	{
		// When mouse is first clicked it will get the initial position, and set mouse clicked variable to true
		if (!mouseClicked)
		{
			initialPos.x = input->getMouseX();
			initialPos.y = input->getMouseY();
			mouseClicked = true;
		}
		if (mouseClicked) // when mouse is being clicked it will repeatedly get the current position until the mouse is no longer clicked - the final position.
		{
			finalPos.x = input->getMouseX();
			finalPos.y = input->getMouseY();
		}	
	}

	// Resets mouse clicked variable when the mouse is not being clicked, calculates and displays length of drag
	if (!input->isMouseLDown() && mouseClicked)
	{
		mouseClicked = false;
		xDif = finalPos.x - initialPos.x;
		yDif = finalPos.y - initialPos.y;
		distance = sqrt(xDif * xDif + yDif * yDif);
		std::cout << "Distance of drag: " << distance << "\n";
	}

	// Creates a circle at the position of the mouse when the right mouse button is clicked.
	if (input->isMouseRDown())
	{
		input->setMouseRDown(false);
		circle.setPosition(input->getMouseX() - 20, input->getMouseY() - 20);
	}

	/*
	if (input->isKeyDown(sf::Keyboard::Space))
	{
		input->setKeyUp(sf::Keyboard::Space);
		xDif = finalPos.x - initialPos.x;
		yDif = finalPos.y - initialPos.y;
		distance = sqrt(xDif * xDif + yDif * yDif);
		std::cout << "Initial position: " << initialPos.x << ", " << initialPos.y << "\nFinal position: " << finalPos.x << ", " << finalPos.y << "\nDistance between clicks: " << distance << "\n";
	}
	*/
}

// Update game objects
void Level::update()
{
	// Updates X and Y position of mouse text
	int x = input->getMouseX();
	int y = input->getMouseY();
	mousePos = "Mouse position: " + std::to_string(x) + ", " + std::to_string(y);
	mousePosDisplay.setString(mousePos);

}

// Render level
void Level::render()
{
	beginDraw();
	
	// Draw objects to window
	window->draw(mousePosDisplay);
	window->draw(circle);

	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}