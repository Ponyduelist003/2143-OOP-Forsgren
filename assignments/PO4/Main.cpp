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
	golCell** tempWorld;
	gameOfLife(int height, int width) {
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
		infile >> Rows >> Cols;

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
				World[i][j].isAlive = tempWorld[i][j].isAlive;
			}
		}
	}


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

	bool onWorld(int height, int width) {
		if (height < 0 ) {
			return false;
		}
		else if (height >= Height) {
			return false;
		}

		if (width < 0) {
			return false;
		}
		else if (width >= Width) {
			return false;
		}
		return true;
	}

	void updateNeighbors() {
		int tempNeighbors = 0;
		for (int i = 0; i < Height; i++) {
			for (int j = 0; j < Width; j++) {
				if (onWorld(i - 1, j - 1)) {
					if (World[i - 1][j - 1].isAlive) {
						tempNeighbors++;
					}
				}
				if (onWorld(i - 1, j)) {
					if (World[i - 1][j].isAlive) {
						tempNeighbors++;
					}
				}
				if (onWorld(i - 1, j + 1)) {
					if (World[i - 1][j + 1].isAlive) {
						tempNeighbors++;
					}
				}
				if (onWorld(i, j - 1)) {
					if (World[i][j - 1].isAlive) {
						tempNeighbors++;
					}
				}
				if (onWorld(i, j + 1)) {
					if (World[i][j + 1].isAlive) {
						tempNeighbors++;
					}
				}
				if (onWorld(i + 1, j - 1)) {
					if (World[i + 1][j - 1].isAlive) {
						tempNeighbors++;
					}
				}
				if (onWorld(i + 1, j)) {
					if (World[i + 1][j].isAlive) {
						tempNeighbors++;
					}
				}
				if (onWorld(i + 1, j + 1)) {
					if (World[i + 1][j + 1].isAlive) {
						tempNeighbors++;
					}
				}
				World[i][j].neighborCount = tempNeighbors;
				tempNeighbors = 0;
			}
		}
	}

	void run(int iteration) {
		for (int i = 0; i < iteration; i++) {
			updateNeighbors();
			for (int j = 0; j < Height; j++) {
				for (int k = 0; k < Width; k++) {
					if (World[j][k].neighborCount < 2) {
						World[j][k].isAlive = false;
					}
					else if (World[j][k].neighborCount = 2 && World[j][k].isAlive){
						World[j][k].isAlive = true;
					}
					else if (World[j][k].neighborCount = 3) {
						World[j][j].isAlive = true;
					}
					else {
						World[j][k].isAlive = false;
					}
				}
			}
		}

	}

	void printBoard(std::ofstream& outfile) {
		outfile << "Griffin Forsgren\n";
		for (int i = 0; i < Height; i++) {
			for (int j = 0; j < Width; j++) {
				if (World[i][j].isAlive) {
					outfile << "1";
				}
				else {
					outfile << "0";
				}
			}
			outfile << "\n";
		}
	}
};



int main() {

	gameOfLife Gol(600, 600);
	std::ifstream infile;
	std::ofstream outfile;
	infile.open("filename.txt");
	outfile.open("outfilename.txt");
	Gol.initBoard(infile);
	while (Gol.Window.isOpen())
	{
		Event event;
		while (Gol.Window.pollEvent(event))
		{
			Gol.run(1);
			Gol.drawWorld();
			system("pause");
			if (event.type == Event::Closed)
				Gol.Window.close();
		}
	}
	Gol.printBoard(outfile);
	return 0;
}
