/*
* Course: CMPS 2143 - OOP
* Assignment: A05 Counter Class
* Purpose: Create a class which can create a counter to increment or decrement
*
* @author Ponyduelist003
* @version 1.1 01/03/17
* @github repo: https://github.com/2143-OOP-Forsgren
*/

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

/*
* Default Constructor for Counter
*
* @param n/a
* @return {Counter} initialized counter
*/
Counter::Counter() {
	start = seconds(0);
	end = seconds(0);
	startHolder = 0;
	endHolder = 0;
}

/*
* Single int Constructor for Counter
*
* @param {int} starting value
* @return {Counter} initialized counter
*/
Counter::Counter(int t) {
	char response;
	// if t is 0, counter must clearly go up
	if (t == 0) {
		start = seconds(t);
		end = seconds(3600);
	}
	//else, determine if increment or decrement
	else {
		std::cout << "Do you want to increment (I) or decrement (D)?" << std::endl;
		std::cin >> response;
		//while response is not I or D
		while (response != 'I' && response != 'D') {
			//if response is invalid, request new response
			if (response != 'I' && response != 'D') {
				std::cout << "Please type I for increment or D for decrement..." << std::endl;
				std::cin >> response;
			}
			//if increment, set for increment
			else if (response == 'I') {
				start = seconds(t);
				end = seconds(3600);
			}
			//else, set for decrement
			else {
				start = seconds(t);
				end = seconds(-3600);
			}
		}
	}
}

/*
* Two int Constructor for Counter
*
* @param {int} {int} starting and ending values
* @return {Counter} initialized counter
*/
Counter::Counter(int s, int e) {
	//if s is greater than e, clearly decrementing
	if (s > e) {
		start = seconds(s + 1);
		end = seconds(e);
	}
	//else, clearly incrementing
	else {
		start = seconds(s);
		end = seconds(e + 2);
	}
	startHolder = s;
	endHolder = e;
}

/*
* Getter for counter's clock
*
* @param n/a
* @return {Clock} current clock
*/
Clock Counter::getClock() {
	return clock;
}

/*
* Getter for counter's elapsed time
*
* @param n/a
* @return {Time} current time elapsed
*/
Time Counter::getElapsed() {
	return elapsed;
}

/*
* Getter for counter's end time
*
* @param n/a
* @return {Time} time at end
*/
Time Counter::getEnd() {
	return end;
}

/*
* Getter for counter's start time
*
* @param n/a
* @return {Time} time at start
*/
Time Counter::getStart() {
	return start;
}

/*
* Set time elapsed for clock to start
*
* @param n/a
* @return n/a
*/
void Counter::setElapsed() {
	elapsed = clock.getElapsedTime();
}

/*
* Determines if counter is done or not
*
* @param n/a
* @return {Bool} is finished or not
*/
bool Counter::isFinished() {
	//if start is greater than end, check if the difference between starting and elapsed time is less than or equal to end time
	if (start > end) {
		return start.asSeconds() - elapsed.asSeconds() <= end.asSeconds();
	}
	//else, check if the sum of starting and elapsed time is greater than or equal to end
	return start.asSeconds() + elapsed.asSeconds() >= end.asSeconds();
}

/*
* Decrement the clock
*
* @param n/a
* @return n/a
*/
void Counter::decrement() {
	//if end is greater than or equal to start, throw an error
	if (end >= start) {
		std::cout << "Error! Attempt to decrement when Start is less than End!" << std::endl;
	}
	//else, cout the int difference between starting time and elapsed time
	std::cout << "Decrementing Clock: " << (int) (start.asSeconds() - elapsed.asSeconds()) << std::endl;
}

/*
* Increment the clock
*
* @param n/a
* @return n/a
*/
void Counter::increment() {
	//if end is less than or equal to start, throw and error
	if (end <= start) {
		std::cout << "Error! Attempt to increment when Start is greater than End!" << std::endl;
	}
	//else cout the int sum of starting time and elapsed time
	std::cout << "Incrementing Clock: " << (int)(start.asSeconds() + elapsed.asSeconds()) << std::endl;
}

/*
* Reset the counter
*
* @param n/a
* @return n/a
*/
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

	//Load 7 Segment Font
	Font font;
	font.loadFromFile("Segment7Standard.otf");

	//set text qualities
	Text text;
	text.setFont(font);
	text.setPosition(75, 75);
	text.setCharacterSize(50);
	text.setFillColor(Color::Red);

	//set flags for later
	int flag = 0;
	int flag2 = 0;

	//while the window is open
	while (window.isOpen())
	{
		Event event;
		//while event is ongoing
		while (window.pollEvent(event))
		{
			//if the event is closed, close window
			if (event.type == Event::Closed)
				window.close();
		}

		//clear the window before everything
		window.clear();

		//set the first clock to start
		myClock1.setElapsed();

		//if the first clock isn't finished
		if (!myClock1.isFinished()) {
			//set the first clock to decrement, put the int timer on window
			myClock1.decrement();
			text.setString(std::to_string((int)(myClock1.getStart().asSeconds() - myClock1.getElapsed().asSeconds())));
			window.draw(text);
			window.display();
		}
		//else, start the second clock and put the int timer on window
		else if(!myClock2.isFinished()){
			myClock2.setElapsed();
			myClock2.increment();
			//while flag is 0, reset elapsed time and increase flag
			while (flag == 0) {
				myClock2.reset();
				flag++;
			}
			text.setString(std::to_string((int)myClock2.getElapsed().asSeconds()));
			window.clear();
			window.draw(text);
			window.display();
			//if second clock is finished, close window
		}
	}
	return 0;
}
