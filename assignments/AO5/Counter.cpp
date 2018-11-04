#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>

// https://www.sfml-dev.org/tutorials/2.5/system-time.php

using namespace sf;

class Counter {
	Clock clock;
	Time start;
	Time end;
	Time elapsed;
	int startHolder;
	int endHolder;

public:

	Counter();
	Counter(int t);
	Counter(int s, int e);
	Clock getClock();
	Time getElapsed();
	Time getStart();
	Time getEnd();
	void setElapsed();
	bool isFinished();
	void decrement();
	void increment();
	void reset();
};

Counter::Counter() {
	start = seconds(0);
	end = seconds(0);
	startHolder = 0;
	endHolder = 0;
}

Counter::Counter(int t) {
	char response;
	if (t == 0) {
		start = seconds(t);
		end = seconds(3600);
	}
	else {
		std::cout << "Do you want to increment (I) or decrement (D)?" << std::endl;
		std::cin >> response;
		while (response != 'I' && response != 'D') {
			if (response != 'I' && response != 'D') {
				std::cout << "Please type I for increment or D for decrement..." << std::endl;
				std::cin >> response;
			}
			else if (response == 'I') {
				start = seconds(t);
				end = seconds(3600);
			}
			else {
				start = seconds(t);
				end = seconds(-3600);
			}
		}
	}
}

Counter::Counter(int s, int e) {
	if (s > e) {
		start = seconds(s + 1);
		end = seconds(e);
	}
	else {
		start = seconds(s);
		end = seconds(e + 1);
	}
	startHolder = s;
	endHolder = e;
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

bool Counter::isFinished() {
	if (start > end) {
		return start.asSeconds() - elapsed.asSeconds() <= end.asSeconds();
	}
	return start.asSeconds() + elapsed.asSeconds() >= end.asSeconds();
}

void Counter::decrement() {
	if (end >= start) {
		std::cout << "Error! Attempt to decrement when Start is less than End!" << std::endl;
	}
	std::cout << "Decrementing Clock: " << (int) (start.asSeconds() - elapsed.asSeconds()) << std::endl;
}

void Counter::increment() {
	if (end <= start) {
		std::cout << "Error! Attempt to increment when Start is greater than End!" << std::endl;
	}
	std::cout << "Incrementing Clock: " << (int)elapsed.asSeconds() << std::endl;
}

void Counter::reset() {
	clock.restart();
	start = seconds(startHolder);
	end = seconds(endHolder);
	elapsed = clock.getElapsedTime();
}

int main()
{
	RenderWindow window(VideoMode(200, 200), "SFML works!");

	Counter myClock1(5, 0); // start at 5 and decrement to 0

	Counter myClock2(0, 5); // start at 0 and increment to 5

	Counter myClock3(5);

	Font font;
	font.loadFromFile("Segment7Standard.otf");

	Text text;


	text.setFont(font);
	text.setPosition(50, 50);
	text.setCharacterSize(24);
	text.setFillColor(Color::Red);
	int flag = 0;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();

		if (!myClock1.isFinished()) {
			myClock1.setElapsed();
			myClock1.decrement();
			text.setString(std::to_string((int)(myClock1.getStart().asSeconds() - myClock1.getElapsed().asSeconds())));
			window.draw(text);
			window.display();
		}
		else{
			myClock2.setElapsed();
			myClock2.increment();
			while (flag == 0) {
				myClock2.reset();
				flag++;
			}
			text.setString(std::to_string((int)myClock2.getElapsed().asSeconds()));
			window.clear();
			window.draw(text);
			window.display();
			if (myClock2.isFinished()) {
				window.close();
			}
		}
	}

	return 0;
}
