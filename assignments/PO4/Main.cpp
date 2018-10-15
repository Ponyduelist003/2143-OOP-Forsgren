/*
*  Course: CMPS 2143 - OOP
*  Assignment: P04
*  Purpose: Simulate Conway's Game of Life
*
*  @author Ponyduelist003
*  @version 1.1 01/03/17
*  @github repo: https://github.com/2143-OOP-Forsgren
*/

#include <SFML/Graphics.hpp>
#include <fstream>
#include <cstring>
#include <iostream>

using namespace sf;

struct golCell {
	bool isAlive;
	int neighborCount;
	RectangleShape Rect;
	int Width;
	int Height;
	
	/**
	*  Constructs a game of life cell
	*
	*  @param n/a
	*  @return {golCell} defaultly constructed
	*/
	golCell() {
		Width = 10;
		Height = 10;
		Rect.setSize(sf::Vector2f(Width, Height));
		Rect.setFillColor(Color::Green);
		Rect.setOutlineColor(Color::Black);
		Rect.setOutlineThickness(1);
		neighborCount = 0;
	}

	/**
	*  Sets the position of a game of life cell
	*
	*  @param {int} {int} x and y coordinates
	*  @return n/a
	*/
	void setCellPos(int x, int y) {
		Rect.setPosition(x*Width, y*Height);
	}

};

struct gameOfLife {
	int Width;
	int Height;
	RenderWindow Window;
	golCell** World;
	golCell** tempWorld;
	/**
	*  Constructs a board for the game of life
	*
	*  @param {int} {int} height and width of board
	*  @return {gameOfLife} fully constructed
	*/
	gameOfLife(int height, int width) {
		Width = width;
		Height = height;
		Window.create(VideoMode(Width * 10, Height * 10), "Game of Life");

		World = new golCell*[height];

		for (int i = 0; i < height; i++) {
			World[i] = new golCell[width];
			for (int j = 0; j < width; j++) {
				World[i][j].setCellPos(i, j);
				World[i][j].isAlive = false;
			}
		}
	}

	/**
	*  Initializes the board for the game of life
	*
	*  @param {ifstream} infile for the game of life cell values
	*  @return n/a
	*/
	void initBoard(std::ifstream &infile) {
		int Cols;
		int Rows;
		std::string line;
		// Reads in first two numbers from first line
		infile >> Cols >> Rows;

		// Dynamically allocate proper number of rows
		tempWorld = new golCell*[Rows];

		// Dynamically allocate proper number of cols
		for (int i = 0; i < Rows; i++) {
			tempWorld[i] = new golCell[Cols];
		}

		// Now Let's read rest of file (0's and 1's)
		for (int i = 0; i < Rows; i++) {
			// Read an entire line in from file
			infile >> line;

			// Loop through the line and insert a 
			// char at a time into the array
			for (int j = 0; j < Cols; j++) {
				tempWorld[i][j].isAlive = (line[j] == '1');
				World[j][i].isAlive = tempWorld[i][j].isAlive;
			}
		}
	}

	/**
	*  draw the board of the game of life in SFML
	*
	*  @param n/a
	*  @return n/a
	*/
	void drawWorld() {
		Window.clear();
		for (int i = 0; i < Height; i++) {
			for (int j = 0; j < Width; j++) {
				if (World[i][j].isAlive) {
					Window.draw(World[i][j].Rect);
				}
			}
		}
		Window.display();
	}

	/**
	*  Check if a position is on the board
	*
	*  @param {int} {int} height and width position
	*  @return {bool} whether or not position is on the board
	*/
	bool onWorld(int height, int width) {
		//if height is less then 0 or greater than/equal to board's Height
		if (height < 0 ) {
			return false;
		}
		else if (height >= Height) {
			return false;
		}

		//if width is less then 0 or greater than/equal to board's Width
		if (width < 0) {
			return false;
		}
		else if (width >= Width) {
			return false;
		}
		return true;
	}

	/**
	*  Updates the neighbor count for all cells on the board
	*
	*  @param n/a
	*  @return n/a
	*/
	void updateNeighbors() {
		//for i going from 0 to height
		for (int i = 0; i < Height; i++) {
			//for j going from 0 to width
			for (int j = 0; j < Width; j++) {
				//make sure neighbor count is 0 to start
				World[i][j].neighborCount = 0;

				//check if each adjacent position is on board and if so, if the cell there is alive.
				//if both are true, increment neighborCount
				if (onWorld(i - 1, j - 1)) {
					if (World[i - 1][j - 1].isAlive) {
						World[i][j].neighborCount++;
					}
				}
				if (onWorld(i - 1, j)) {
					if (World[i - 1][j].isAlive) {
						World[i][j].neighborCount++;
					}
				}
				if (onWorld(i - 1, j + 1)) {
					if (World[i - 1][j + 1].isAlive) {
						World[i][j].neighborCount++;
					}
				}
				if (onWorld(i, j - 1)) {
					if (World[i][j - 1].isAlive) {
						World[i][j].neighborCount++;
					}
				}
				if (onWorld(i, j + 1)) {
					if (World[i][j + 1].isAlive) {
						World[i][j].neighborCount++;
					}
				}
				if (onWorld(i + 1, j - 1)) {
					if (World[i + 1][j - 1].isAlive) {
						World[i][j].neighborCount++;
					}
				}
				if (onWorld(i + 1, j)) {
					if (World[i + 1][j].isAlive) {
						World[i][j].neighborCount++;
					}
				}
				if (onWorld(i + 1, j + 1)) {
					if (World[i + 1][j + 1].isAlive) {
						World[i][j].neighborCount++;
					}
				}
			}
		}
	}

	/**
	*  runs the game of life for a number of iterations
	*
	*  @param {int} iterations of the game of life
	*  @return n/a
	*/
	void run(int iteration) {
		//for every iteration
		for (int i = 0; i < iteration; i++) {
			//update the neighbor count
			updateNeighbors();
			//for j going from 0 to height
			for (int j = 0; j < Height; j++) {
				//for k going from 0 to width
				for (int k = 0; k < Width; k++) {
					//if a cell has less than 2 neighbors, it dies
					if (World[j][k].neighborCount < 2) {
						World[j][k].isAlive = false;
					}
					//if a cell has exactly 3 neighbors, it comes to life
					else if (World[j][k].neighborCount == 3) {
						World[j][k].isAlive = true;
					}
					//if a cell has more than 3 neighbors, it dies
					else if (World[j][k].neighborCount > 3){
						World[j][k].isAlive = false;
					}
					//if a cell falls under none of these (i.e. has 2 neighbors), it is unchanged.
				}
			}
		}

	}
	/**
	*  prints the board of the game of life to an outfile
	*
	*  @param {ofstream} outfile to print to
	*  @return n/a
	*/
	void printBoard(std::ofstream& outfile) {
		//print name first
		outfile << "Griffin Forsgren\n";
		//for i going from 0 to height
		for (int i = 0; i < Height; i++) {
			//for j going from 0 to width
			for (int j = 0; j < Width; j++) {
				//if the cell is alive, outfile 1. If the cell is dead, outfile 0.
				if (World[i][j].isAlive) {
					outfile << "1";
				}
				else {
					outfile << "0";
				}
			}
			//outfile end of line before going to next row
			outfile << "\n";
		}
	}
};



int main() {
	//declare a game of life board
	gameOfLife Gol(40, 50);

	//open infile and outfile
	std::ifstream infile;
	std::ofstream outfile;
	infile.open("filename.txt");
	outfile.open("outfilename.txt");

	//initialize the board
	Gol.initBoard(infile);

	//run the board for 338 iterations
	Gol.run(338);

	//while the window is open
	while (Gol.Window.isOpen())
	{
		Event event;
		while (Gol.Window.pollEvent(event))
		{
			//draw the final result of the iterations
			Gol.drawWorld();
			if (event.type == Event::Closed)
				Gol.Window.close();
		}
	}

	//print the result to an oufile
	Gol.printBoard(outfile);

	//close the file streams
	infile.close();
	outfile.close();
	return 0;
}
