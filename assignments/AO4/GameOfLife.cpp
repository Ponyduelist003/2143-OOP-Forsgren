/**
*  Course: CMPS 2143 - OOP
*  Assignment: AO4
*  Purpose: Recreate Conway's Game of Life
*
*  @Author Ponyduelist003
*  @Version 1.1 01/03/17
*  @github repo: https://github.com/2143-OOP-Forsgren
*/

#include <SFML/Graphics.hpp>

using namespace sf;

struct golCell {
	bool isAlive;
	int neighborCount;
	RectangleShape Rect;
	int Width;
	int Height;
	
	/**
	*  Establish a cell in the Game of Life
	*
	*  @param n/a
	*  @return n/a
	*/
	golCell() {
		Width = 10;
		Height = 10;
		Rect.setSize(sf::Vector2f(Width, Height));
		Rect.setFillColor(Color::Green);
		Rect.setOutlineColor(Color::Black);
		Rect.setOutlineThickness(1);
	}
	
	/**
	*  Sets the position of the cell
	*
	*  @param {int} {int} x and y position of cell
	*  @return n/a
	*/
	void setCellPos(int x, int y) {
		Rect.setPosition(x*Width, y*Height);
	}

};

struct gameOfLife {
	int Width;
	int Height;
	int FrameCount;
	int FrameRate;
	RenderWindow Window;
	golCell** World;
	
	/**
	*  Establishes the board for the Game of Life
	*
	*  @param {int} {int} width and height of board
	*  @return n/a
	*/
	gameOfLife(int width, int height) {
		Width = width;
		Height = height;
		FrameCount = 0;
		FrameRate = 5;
		Window.create(VideoMode(Width, Height), "Game of Life");

		World = new golCell*[height];

		for (int i = 0; i < height; i++) {
			World[i] = new golCell[width];
			for (int j = 0; j < width; j++) {
				World[i][j].setCellPos(i, j);
			}
		}
	}
	
	/**
	*  Draws the world for the Game of Life
	*
	*  @param n/a
	*  @return n/a
	*/
	void drawWorld() {
		Window.clear();
		for (int i = 0; i < Height; i++) {
			for (int j = 0; j < Width; j++) {
				Window.draw(World[i][j].Rect);
			}
		}
		Window.display();
	}
};

int main() {
	gameOfLife Gol(1000, 1000);
	while (Gol.Window.isOpen())
	{
		Event event;
		while (Gol.Window.pollEvent(event))
		{
			if (Gol.FrameCount % Gol.FrameRate == 0) {
				Gol.drawWorld();
			}
			else if (event.type == Event::Closed) {
				Gol.Window.close();
			}
			Gol.FrameCount++;
		}
	}
	return 0;
}
