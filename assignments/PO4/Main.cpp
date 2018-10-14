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

	golCell() {
		Width = 10;
		Height = 10;
		Rect.setSize(sf::Vector2f(Width, Height));
		Rect.setFillColor(Color::Green);
		Rect.setOutlineColor(Color::Black);
		Rect.setOutlineThickness(1);
	}

	void setCellPos(int x, int y) {
		Rect.setPosition(x*Width, y*Height);
	}

};

struct gameOfLife {
	int Width;
	int Height;
	RenderWindow Window;
	golCell** World;
	gameOfLife(int width, int height) {
		Width = width;
		Height = height;
		Window.create(VideoMode(Width, Height), "Game of Life");

		World = new golCell*[height];

		for (int i = 0; i < height; i++) {
			World[i] = new golCell[width];
			for (int j = 0; j < width; j++) {
				World[i][j].setCellPos(i, j);
				World[i][j].isAlive = false;
			}
		}
	}

	void initBoard(std::ifstream &infile) {
		int Cols;
		int Rows;
		std::string line;
		// Reads in first two numbers from first line
		infile >> Cols >> Rows;

		// Dynamically allocate proper number of rows
		World = new golCell*[Rows];

		// Dynamically allocate proper number of cols
		for (int i = 0; i < Rows; i++) {
			World[i] = new golCell[Cols];
		}

		// Now Let's read rest of file (0's and 1's)
		for (int i = 0; i < Rows; i++) {
			// Read an entire line in from file
			infile >> line;

			// Loop through the line and insert a 
			// char at a time into the array
			for (int j = 0; j < Cols; j++) {
				World[i][j].isAlive = line[j] - 48;
			}
		}
	}


	void drawWorld() {
		Window.clear();
		for (int i = 0; i < Height; i++) {
			for (int j = 0; j < Width; j++) {
				Window.draw(World[i][j].Rect);
			}
		}
		Window.display();
	}

	void updateNeighbors() {
		int tempNeighbors = 0;
		for (int i = 0; i < Height; i++) {
			for (int j = 0; j < Width; j++) {
				if (i - 1 >= 0 && j - 1 >= 0 && World[i - 1][j - 1].isAlive) {
					tempNeighbors++;
				}
				if (i - 1 >= 0 && World[i - 1][j].isAlive) {
					tempNeighbors++;
				}
				if (i - 1 >= 0 && j + 1 < Width && World[i - 1][j + 1].isAlive) {
					tempNeighbors++;
				}
				if (j - 1 >= 0 && World[i][j - 1].isAlive) {
					tempNeighbors++;
				}
				if (j + 1 < Width && World[i][j + 1].isAlive) {
					tempNeighbors++;
				}
				if (i + 1 < Height && j - 1 >= 0 && World[i + 1][j - 1].isAlive) {
					tempNeighbors++;
				}
				if (i + 1 < Height && World[i + 1][j].isAlive) {
					tempNeighbors++;
				}
				if (i + 1 < Height && j + 1 < Width && World[i + 1][j + 1].isAlive) {
					tempNeighbors++;
				}
				World[i][j].neighborCount = tempNeighbors;
				tempNeighbors = 0;
			}
		}
	}

	void run(int iteration) {
		for (int i = 0; i < iteration; i++) {
			updateNeighbors();
			for (int j = 0; i < Height; j++) {
				for (int k = 0; k < Width; k++) {
					if (World[j][k].neighborCount < 2) {
						World[j][k].isAlive = false;
					}
					else if (World[j][k].neighborCount <= 3){
						World[j][k].isAlive = true;
					}
					else {
						World[j][k].isAlive = false;
					}
				}
			}
		}

	}
};



int main() {

	gameOfLife Gol(1000, 1000);
	std::ifstream infile;
	std::ofstream outfile;
	infile.open("filename.txt");
	outfile.open("outfilename.txt");
	Gol.initBoard(infile);
	Gol.run(338);
	while (Gol.Window.isOpen())
	{
		Event event;
		while (Gol.Window.pollEvent(event))
		{
			Gol.drawWorld();
			if (event.type == Event::Closed)
				Gol.Window.close();
		}


	}

	return 0;
}
