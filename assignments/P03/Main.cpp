/**
   *  Course: CMPS 2143 - OOP
   *
   *  Purpose: Make a green dot in SFML
   *
   *  @author Ponyduelist003
   *  @version 1.1 01/03/17
   *  @github repo: https://github.com/2143-OOP-Forsgren
   */
#include <SFML/Graphics.hpp>
int main() {
	//Open a 200 x 200 window to work in
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

	//Make a green circle
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	//While the window is open
	while (window.isOpen()) {
		sf::Event event;
		//while there is an event to pop from queue
		while (window.pollEvent(event)) {
			// if the event is closed, close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//clear the window, draw the circle again, and display
		window.clear();
		window.draw(shape);
		window.display();
	}
	return 0;
}
