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

		edgeX = 400;
		edgeY = 350;
	}

	void changeSmiley(string image) {
		smiley.setTileTexture(image);
	}

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

	int getEdgeX() {
		return edgeX;
	}

	int getEdgeY() {
		return edgeY;
	}
};

class GameClock {
private:
	sf::Text text;          // var to hold clock digits
	sf::Clock gameClock;    // SFML clock type
	sf::Time startTime;
	sf::Font font;
	sf::Color textColor;
	int fontSize;
public:
	GameClock() {
		gameClock.restart();
		if (!font.loadFromFile("Segment7Standard.otf")) {
			cout << "Error loading font 'Segment7Standard.otf'...";
			exit(0);
		}

		fontSize = 48;

		textColor = sf::Color(0, 255, 0); // green

		text.setFont(font); // font is a sf::Font

		// set the string to display
		text.setString("0");

		text.setCharacterSize(fontSize); // in pixels, not points!

		text.setFillColor(textColor);

		text.setStyle(sf::Text::Bold);

	}

	void printClock(sf::RenderWindow &window, int gameWidth, int gameHeight) {

		int itime = gameClock.getElapsedTime().asSeconds();


		string stime = to_string(itime);

		text.setString(stime);

		float textWidth = text.getLocalBounds().width;
		float textHeight = text.getLocalBounds().height;

		sf::Vector2f coord(gameWidth / 2, gameHeight / 2);
		sf::Vector2f origin(textWidth / 2.0f, textHeight / 2.0f);

		text.setOrigin(origin);
		text.setPosition(coord);

		window.draw(text);
	}
};

int main()
{

	DrawMe D;
	GameClock G;

	sf::RenderWindow window(sf::VideoMode(D.getEdgeX(), D.getEdgeY()), "SFML Smiley!");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			D.changeSmiley("./surprised.png");
		}

		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			D.changeSmiley("./smiley.png");
		}

		window.clear();
		window.draw(D);
		G.printClock(window, 300, 300);
		D.update();

		window.display();
	}

	return 0;
}
