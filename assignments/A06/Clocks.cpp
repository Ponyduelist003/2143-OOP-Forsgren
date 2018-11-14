/*
* Course: CMPS 2143 - OOP
* Assignment: A06 Bouncing Clock
* Purpose: Create a clock that bounces off the walls of the window
*
* @author Ponyduelist003
* @version 1.1 01/03/17
* @github repo: https://github.com/2143-OOP-Forsgren
*/
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Tile.h"
#include "Group.h"

using namespace std;

// https://d2trtkcohkrm90.cloudfront.net/images/emoji/apple/ios-11/128/slightly-smiling-face.png



class DrawMe : public Group {
private:
	Tile smiley;
	sf::RectangleShape rectangle;
	float shiftX;
	float shiftY;
	int edgeX;
	int edgeY;
public:

	/*
	* Default Constructor for DrawMe
	*
	* @param n/a
	* @return {DrawMe} initialized
	*/
	DrawMe() {

		smiley.resetTile(128, 128, "./smiley.png");
		smiley.setPosition(sf::Vector2f(100.0, 100.0));
		smiley.setSize(64, 64);
		smiley.setOrigin(64.0, 64.0);
		

		rectangle.setSize(sf::Vector2f(100, 100));
		rectangle.setFillColor(sf::Color::Black);
		rectangle.setOutlineColor(sf::Color::Green);
		rectangle.setOutlineThickness(2);
		rectangle.setOrigin(50, 50);
		rectangle.setPosition(100, 100);

		shiftX = 1;
		shiftY = 1;

		this->push_back(rectangle);
		this->push_back(smiley);

		edgeX = 300;
		edgeY = 300;
	}

	/*
	* Change the smiley's texture
	*
	* @param {string} texture image
	* @return n/a
	*/
	void changeSmiley(string image) {
		smiley.setTileTexture(image);
	}

	/*
	* Update position of rectangle and smiley
	* 
	* @param n/a
	* @return n/a
	*/
	void update() {
		rectangle.move(shiftX, shiftY);
		smiley.move(shiftX, shiftY);

		if (rectangle.getPosition().x + 50 >= edgeX || rectangle.getPosition().x - 50 <= 0) {
			shiftX *= -1;
		}
		if (rectangle.getPosition().y + 50 >= edgeY || rectangle.getPosition().y - 50 <= 0) {
			shiftY *= -1;
		}
	}
};

class GameClock{
private:
	sf::Text text;          // var to hold clock digits
	sf::Clock gameClock;    // SFML clock type
	sf::Time startTime;
	sf::Font font;
	sf::Color textColor;
	sf::RectangleShape rectangle;

	int shiftX;
	int shiftY;
	int edgeX;
	int edgeY;

	int fontSize;
public:

	/*
	* Default constructor for GameClock
	*
	* @param n/a
	* @return {GameClock} initialized
	*/
	GameClock() {
		gameClock.restart();
		if (!font.loadFromFile("Segment7Standard.otf")) {
			cout << "Error loading font 'Segment7Standard.otf'...";
			exit(0);
		}

		rectangle.setSize(sf::Vector2f(100, 100));
		rectangle.setFillColor(sf::Color::Black);
		rectangle.setOutlineColor(sf::Color::Green);
		rectangle.setOutlineThickness(2);
		rectangle.setOrigin(50, 50);
		rectangle.setPosition(100, 100);

		shiftX = 1;
		shiftY = 1;

		edgeX = 300;
		edgeY = 300;

		fontSize = 50;

		textColor = sf::Color(0, 255, 0); // green

		text.setFont(font); // font is a sf::Font

		// set the string to display
		text.setString("0");

		text.setCharacterSize(fontSize); // in pixels, not points!

		text.setFillColor(textColor);

		text.setStyle(sf::Text::Bold);

	}

	/*
	* Set the font of the text
	*
	* @param {string} file of new font
	* @return n/a
	*/
	void setFont(string newFont) {
		font.loadFromFile(newFont);
		text.setFont(font);
	}

	/*
	* Set the color of the background
	*
	* @param {int} {int} {int} red green and blue values
	* @return n/a
	*/
	void setBackground(int r, int g, int b) {
		rectangle.setFillColor(sf::Color(r, g, b));
	}

	/*
	* Set the color of the font
	*
	* @param {int} {int} {int} red green and blue values
	* @return n/a
	*/
	void setFontColor(int r, int g, int b) {
		text.setFillColor(sf::Color(r, g, b));
	}

	/*
	* Set the color of the border
	*
	* @param {int} {int} {int} red green and blue values
	* @return n/a
	*/
	void setBorderColor(int r, int g, int b) {
		rectangle.setOutlineColor(sf::Color(r, g, b));
	}

	/*
	* Print out the clock
	*
	* @param {window} {int} {int} window to print to and dimensions
	* @return n/a
	*/
	void printClock(sf::RenderWindow &window, int gameWidth, int gameHeight) {

		int itime = gameClock.getElapsedTime().asSeconds();


		string stime = to_string(itime);

		text.setString(stime);

		float textWidth = text.getLocalBounds().width;
		float textHeight = text.getLocalBounds().height;

		sf::Vector2f coord(rectangle.getPosition().x, rectangle.getPosition().y);
		sf::Vector2f origin(30, 30);

		text.setOrigin(origin);
		text.setPosition(coord);

		rectangle.move(shiftX, shiftY);
		text.move(shiftX, shiftY);

		//if the rectangle's edge meets the window's edge, reverse the shift
		if (rectangle.getPosition().x + 50 >= edgeX || rectangle.getPosition().x - 50 <= 0) {
			shiftX *= -1;
		}
		if (rectangle.getPosition().y + 50 >= edgeY || rectangle.getPosition().y - 50 <= 0) {
			shiftY *= -1;
		}

		window.draw(rectangle);
		window.draw(text);
	}
};

int main()
{
	//Initialize SFML functions
	DrawMe D;
	GameClock G;
	sf::RenderWindow window(sf::VideoMode(300, 300), "SFML Smiley!");

	//while window is open
	while (window.isOpen())
	{
		sf::Event event;
		//while event is ongoing, if event is closed close the window
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//if the button is pressed, change the smiley
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			D.changeSmiley("./surprised.png");
		}

		//if the button isn't pressed, normal smiley
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			D.changeSmiley("./smiley.png");
		}

		//clear window, draw, print the clock, update and display
		window.clear();
		window.draw(D);
		G.printClock(window, 300, 300);
		D.update();
		window.display();
	}
	return 0;
}
