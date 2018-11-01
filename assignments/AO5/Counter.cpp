#include <SFML/Graphics.hpp>
#include <iostream>

// https://www.sfml-dev.org/tutorials/2.5/system-time.php

using namespace std;

class Counter {
	int start;
	int end;

};

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

	Counter myClock1(5, 0); // start at 5 and decrement to 0

	Counter myClock2(0, 5); // start at 0 and increment to 5

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		//window.draw(shape);
		window.display();

		if (myClock1.isFinished()) {
			window.close();
		}
	}

	return 0;
}
