#include <SFML/Graphics.hpp>
#include <iostream>

// https://www.sfml-dev.org/tutorials/2.5/system-time.php

using namespace sf;

class Counter {
	Clock clock;
	Time start;
	Time end;
	Time elapsed;

public:

	Counter();
	Counter(int s, int e);
	Clock getClock();
	Time getElapsed();
	Time getStart();
	Time getEnd();
	void setElapsed();
};

Counter::Counter() {
	start = seconds(0);
	end = seconds(0);
}

Counter::Counter(int s, int e) {
	start = seconds(s);
	end = seconds(e);
}

Clock Counter::getClock() {
	return clock;
}

Time Counter::getElapsed() {
	return elapsed;
}

Time Counter::getEnd() {
	return end;
}

Time Counter::getStart() {
	return start;
}

void Counter::setElapsed() {
	elapsed = clock.getElapsedTime();
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");

	//sf::Clock clock;
	//sf::Time start;
	//sf::Time end;
	//sf::Time elapsed;
	//start = sf::seconds(50);
	//end = sf::seconds(50);

	Counter counter(5, 5);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		counter.setElapsed();
		std::cout << "Incrementing Clock: " << (int) counter.getElapsed().asSeconds()<< std::endl;

		counter.getElapsed() = counter.getClock().getElapsedTime();
		std::cout << "Decrementing Clock: " << (int) (counter.getStart().asSeconds() - counter.getElapsed().asSeconds()) << std::endl;
		if (counter.getStart().asSeconds() - counter.getElapsed().asSeconds() <= 0) {
			window.close();
		}
		window.clear();
		//window.draw(shape);
		window.display();
	}

	return 0;
}
