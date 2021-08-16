//si aici am folosit fisiere header si cpp
//GameOfLife.h:
class GameOfLife
{

public:
	void static init_grid();// facut
	void  pick_Menu(); //facut
	void print_grid();
	void Block( int x, int y);
	void Boat(int x , int y);
	void Blinker(int x, int y);
	void Beacon(int x, int y);
	void Glider(int x, int y);
	void DrawShape(int Shape, int x, int y);
	bool checkLess2CellsAround(int xPunct, int yPunct);
	bool check2or3Cells(int xPunct, int yPunct);
	bool checkMore3Cells(int xPunct, int yPunct);
	bool ResurectCell(int xPunct, int yPunct);
	void Redraw(int movements);

};
//end of GameOfLife.h
//GameOfLife.cpp
//#include "GameOfLife.h"
//#include <iostream>
//#include<vector>



const int rows = 20;
const int cols = 20;
int grid[rows][cols];
int pick, xPunct, yPunct, movements;
struct Point {
	int x;
	int y;
	Point(int abs, int ord) {
		this->x = abs;
		this->y = ord;
	}
};

enum Shape {
	Block = 1,
	Boat = 2,
	Blinker = 3,
	Beacon = 4,
	Pulsar = 5,
	Pentadecathlon = 6,
	Glider = 7

};

void GameOfLife::init_grid() {
	for (int x = 0; x < rows; x++) {
		for (int y = 0; y < cols; y++) {
			grid[x][y] = 0;
		}
	}
};

void GameOfLife::print_grid() {
	for (int x = 0; x < rows; x++) {
		for (int y = 0; y < cols; y++) {
			std::cout << grid[x][y] << " ";

		}
		std::cout << std::endl;
	}
};

void GameOfLife::pick_Menu() {
	std::cout << "You can choose the form to display from this list: " << std::endl
		<< "Option 1: Block" << std::endl
		<< "Option 2: Boat" << std::endl
		<< "Option 3: Blinker" << std::endl
		<< "Option 4: Beacon " << std::endl
		<< "Option 5: Glider " << std::endl
		<< "Enter your option: ";
	std::cin >> pick; //the option from user
	std::cout << "Introduce the coordonates. Pick values <= 20." << std::endl;
	do {
		std::cout << "X: ";
		std::cin >> xPunct;
		std::cout << "Y: ";
		std::cin >> yPunct;
		if (xPunct >= 20 || yPunct >= 20)
			std::cout << "Enter the coordinates again." << std::endl;
	} while (xPunct >= 20 && yPunct >= 20);
	std::cout << "Now enter how many movements:" << std::endl;
	std::cin >> movements;
	std::cout << "Show shape:" << std::endl;
	GameOfLife::DrawShape(pick, xPunct, yPunct);
}


void GameOfLife::Block (int x, int y)
{

	grid[x - 1][y - 1] = 1;
	grid[x][y - 1] = 1;
	grid[x - 1][y] = 1;
	grid[x][y] = 1;
}

void GameOfLife::Boat (int x, int y)
{
	grid[x - 1][y - 1] = 1;
	grid[x][y - 1] = 1;
	grid[x - 1][y] = 1;
	grid[x][y + 1] = 1;
	grid[x + 1][y] = 1;
}

void GameOfLife::Blinker(int x, int y)
{
	grid[x - 1][y - 1] = 1;
	grid[x - 1][y - 2] = 1;
	grid[x - 1][y ] = 1;
}

void GameOfLife::Beacon(int x, int y)

{
	//top left part
	grid[x - 1][y - 1] = 1;
	grid[x][y - 1] = 1;
	grid[x - 1][y] = 1;
	//bottom right part
	grid[x + 2][y + 1] = 1;
	grid[x + 1][y + 2] = 1;
	grid[x + 2][y + 2] = 1;
}

void GameOfLife::Glider(int x, int y)
{
	grid[x - 2][y - 1] = 1;
	grid[x - 1][y] = 1;
	grid[x][y] = 1;
	grid[x][y - 1] = 1;
	grid[x][y - 2] = 1;
}

void GameOfLife::Redraw(int movements) {
	for (int i = 0; i < movements; ++i) {
		std::vector<Point> deaths;
		std::vector<Point> alive;
		for (int i = 0; i < rows; i++)
			for (int j = 0; j < cols; j++)
				if (grid[i][j] == 1) {
					if (GameOfLife::checkLess2CellsAround(i, j) || GameOfLife::checkMore3Cells(i, j)) {
						Point p(i, j);
						deaths.push_back(p);
					}
					else if (GameOfLife::check2or3Cells(i, j)) {
						Point p(i, j);
						alive.push_back(p);
					}
				}
				else if (grid[i][j] == 0) {
					if (GameOfLife::ResurectCell(i, j)) {
						Point p(i, j);
						//cout << i << " " << j << endl;;
						alive.push_back(p);
					}
				}

		for (Point p : alive)
			grid[p.x][p.y] = 1;
		for (Point p : deaths)
			grid[p.x][p.y] = 0;

		std::cout << std::endl;
		GameOfLife::print_grid();
	}
}

bool GameOfLife::ResurectCell(int xPunct, int yPunct) {
	int counter = 0;
	for (int row = xPunct - 1; row < xPunct + 2 && row < rows; ++row)
	{
		for (int col = yPunct - 1; col < yPunct + 2 && col < cols; ++col)
		{
			if (grid[row][col])
				counter++;
		}
	}

	return counter == 3;
}

bool GameOfLife::checkLess2CellsAround(int xPunct, int yPunct) {
	int count = 0;
	for (int row = xPunct - 1; row < xPunct + 2 && row < rows; ++row)
	{
		for (int col = yPunct - 1; col < yPunct + 2 && col < cols; ++col)
		{
			if (grid[row][col])
				count++;

		}
	}
	return (count - 1) < 2;
}

bool GameOfLife::checkMore3Cells(int xPunct, int yPunct) {
	int count = 0;
	for (int row = xPunct - 1; row < xPunct + 2 && row < rows; ++row)
	{
		for (int col = yPunct - 1; col < yPunct + 2 && col < cols; ++col)
		{
			if (grid[row][col])
				count++;

		}
	}
	return (count - 1) > 3;
}

bool GameOfLife::check2or3Cells(int xPunct, int yPunct) {
	int count = 0;
	for (int row = xPunct - 1; row < xPunct + 2 && row < rows; ++row)
	{
		for (int col = yPunct - 1; col < yPunct + 2 && col < cols; ++col)
		{
			if (grid[row][col])
				count++;

		}
	}
	return count == 2 || count == 3;
}

void GameOfLife::DrawShape(int Shape, int Xcoord, int Ycoord) {

	switch (Shape) {
	case 1: {
		GameOfLife::Block(Xcoord, Ycoord);
		GameOfLife::print_grid();
		GameOfLife::Redraw(movements);
		break;
	}
	case 2: {
		GameOfLife::Boat(Xcoord, Ycoord);
		GameOfLife::print_grid();
		GameOfLife::Redraw(movements);
		break;
	}
	case 3: {
		GameOfLife::Blinker(Xcoord, Ycoord);
		GameOfLife::print_grid();
		GameOfLife::Redraw(movements);
		break;
	}
	case 4: {
		GameOfLife::Beacon(Xcoord, Ycoord);
		GameOfLife::print_grid();
		GameOfLife::Redraw(movements);
		break;
	}

	case 5: {
		GameOfLife::Glider(Xcoord, Ycoord);
		GameOfLife::print_grid();
		GameOfLife::Redraw(movements);
		break;
	}
	default: {
		std::cout << "Wrong figure input.";
		break;
	}
	}


}
//eof GameOfLife.cpp


int main()
{
	std::cout << "Assigment 4 Game of Life on 20x20 grid" << std::endl;
	GameOfLife var;
	var.init_grid();
	//var.print_grid();
	var.pick_Menu();
	return 0;
}
