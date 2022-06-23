#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <windows.h>
#define MAXSIZE 100
#define NORTH 0
#define EAST 1
#define SOUTH 2
#define WEST 3

using namespace std;

class MAZE
{
public:

	void playGame() { //to gamify using values
		cout << "Enter Size of Maze:" << endl;
		cin >> size;
		while ((size < 10 || size > 100)) {
			cout << "Invalid Size Please Enter Again:" << endl;
			cin >> size;
			system("cls");
		}
		cout << "    -------------------MAZEGAME--------------------" << endl << endl;
		cout << "   'O' : Coin --> If you collect, your score will increase." << endl;
		cout << "   '�' : Monster --> The monster steals your coins and sends you to the starting point." << endl;
		cout << "   '.' : Current Location" << endl;
		cout << "   '0' : Path " << endl;
		cout << "   '1' : Wall " << endl;
		cout << "   Keys: 'w' --> up || 's' --> down || 'a' --> left || 'd' --> 'right'" << endl << endl;
		ofstream openFile("saveLocation.txt");
		openFile << " x | y" << endl;
		openFile << "-------" << endl;
		srand(time(0));
		int finish = rand() % size;
		createMaze(finish);
		x = 0;
		y = 0;
		maze[x][y] = '.';
		openFile << " " << x << " | " << y << endl;



		for (;;) {
			printMaze();

			if (x == size - 1 && y == finish) {
				cout << "Congratulation!!" << endl;
				return;
			}

			cout << "Enter move: ";
			cin >> input;
			switch (input)
			{
			case 'w':
				if (isPath(x - 1, y)) {

					x--;
					openFile << " " << x << " | " << y << endl;
					maze[x + 1][y] = '0';
					if (isMonster(x, y)) {
						openFile << " " << x << " | " << y << endl;
					}
					else
					{
						maze[x][y] = '.';

					}
				}
				break;
			case 'a':
				if (isPath(x, y - 1)) {

					y--;
					openFile << " " << x << " | " << y << endl;
					maze[x][y + 1] = '0';
					if (isMonster(x, y)) {
						openFile << " " << x << " | " << y << endl;
					}
					else
					{
						maze[x][y] = '.';

					}

				}
				break;
			case 's':
				if (isPath(x + 1, y)) {

					x++;
					openFile << " " << x << " | " << y << endl;
					maze[x - 1][y] = '0';
					if (isMonster(x, y)) {
						openFile << " " << x << " | " << y << endl;
					}
					else
					{
						maze[x][y] = '.';
					}


				}
				break;
			case 'd':
				if (isPath(x, y + 1)) {
					y++;
					openFile << " " << x << " | " << y << endl;
					maze[x][y - 1] = '0';
					if (isMonster(x, y)) {
						openFile << " " << x << " | " << y << endl;
					}
					else
					{
						maze[x][y] = '.';
					}
				}
				break;
			default:
				cout << "InvalidMove";
				break;
			}


			system("cls");
		}

	}


	bool isMonster(int _x, int _y) {  //this function performs the scenario that will happen if the monster is encountered
		if (maze[_x][_y] == '�') {
			cout << "Monster!!";
			Sleep(1000);

			x = 0;
			y = 0;
			maze[x][y] = '.';

			coin = 0;
			return true;
		}
		return false;
	}

	bool isPath(int _x, int _y) {  //this function checks the appropriateness of the movement
		if (maze[_x][_y] == '1') { cout << "Wall!"; Sleep(400); return false; }
		else if (maze[_x][_y] == '0') { return true; }
		else if (maze[_x][_y] == '�') { return true; }
		else if (maze[_x][_y] == 'O') {
			coin++;
			return true;
		}
		else {
			cout << "Out of range!";
			Sleep(400);
			return false;
		}
	}

	void printMaze() { //maze printing function
		int count = 0;
		cout << "      ";
		while (count < size) {
			cout << setw(4) << left << count;
			count++;
		}
		cout << endl;
		cout << "      ";
		count = 0;
		while (count < size - 1) {
			cout << setw(4) << left << "----";
			count++;
		}
		cout << "-" << endl;
		for (int i = 0; i < size; i++) {
			cout << setw(4) << right << i << "| ";
			for (int y = 0; y < size; y++) {
				if (i == 0 && y == 0) {

				}
				cout << setw(4) << left << maze[i][y];
			}
			cout << endl << endl;
		}
		cout << "Total Coin:" << coin << endl;
	}
	void ResetGrid() //Placing walls before creating maze
	{
		// Fills the grid with walls ('1' characters).
		for (int i = 0; i < size; ++i)
		{
			for (int y = 0; y < size; y++) {
				maze[i][y] = '1';
			}
		}
	}
	bool IsInMaze(int x, int y)
	{
		if (x < 0 || x >= size) return false;
		if (y < 0 || y >= size) return false;
		return true;
	}

	void createMaze(int finish) { //Creating a maze for the game
		maze[size][size];
		ResetGrid();
		Visit(0, 0);
		for (int i = 2; i < size - 2; i++) { //placing monsters
			for (int j = 2; j < size - 2; j++) {

				if (maze[i][j] == '0' && maze[i + 1][j] == '1' && maze[i - 1][j] == '1' && maze[i][j + 1] == '1') {
					maze[i][j] = '�';
				}
				if (maze[i][j] == '0' && maze[i + 1][j] == '1' && maze[i - 1][j] == '1' && maze[i][j - 1] == '1') {
					maze[i][j] = '�';
				}
				if (maze[i][j] == '0' && maze[i][j + 1] == '1' && maze[i + 1][j] == '1' && maze[i][j - 1] == '1') {
					maze[i][j] = '�';
				}
				if (maze[i][j] == '0' && maze[i][j + 1] == '1' && maze[i - 1][j] == '1' && maze[i][j - 1] == '1') {
					maze[i][j] = '�';
				}
			}

		}
		int coinsNumber = size / 2;
		while (coinsNumber > 0) {
			int dx = rand() % size;
			int dy = rand() % size;
			if (maze[dx][dy] == '0') {
				maze[dx][dy] = 'O';
				coinsNumber--;
			}
		}
		if (size % 2 == 1) {
			for (int i = 0; i < size; i++) {
				maze[size - 1][i] = '1';
			}
		}
		for (int i = 0; i < size / 2; i++) {
			maze[size - i][finish] = '0';
			if (size % 2 == 1) {
				for (int i = 0; i < size - 1; i++) {
					maze[size - 2][i] = '0';
				}
			}
		}
	}
	void Visit(int _x, int _y) { // Recursively maze walk function to create maze
		maze[_x][_y] = '0';
		int dirs[4];
		dirs[0] = NORTH;
		dirs[1] = EAST;
		dirs[2] = SOUTH;
		dirs[3] = WEST;
		for (int i = 0; i < 4; ++i) //a loop to randomly distribute directions
		{
			int r = rand() & 3;
			int temp = dirs[r];
			dirs[r] = dirs[i];
			dirs[i] = temp;
		}
		for (int i = 0; i < 4; ++i)
		{
			int dx = 0, dy = 0;
			switch (dirs[i])
			{
			case NORTH: dy = -1; break;
			case SOUTH: dy = 1; break;
			case EAST: dx = 1; break;
			case WEST: dx = -1; break;
			}

			int x2 = _x + (dx << 1);
			int y2 = _y + (dy << 1);
			if (IsInMaze(x2, y2))
			{
				if (maze[x2][y2] == '1')
				{
					// (x2,y2) has not been visited yet... knock down the
					// wall between my current position and that position
					maze[x2 - dx][y2 - dy] = '0';

					Visit(x2, y2); // Recursively Visit (x2,y2)
				}
			}
		}

	}
private:
	char maze[MAXSIZE][MAXSIZE]; //Maze
	char input; // for w a s d keywords
	int size; // for size of maze
	int coin = 0; // coins
	int x, y; // for currently position


};

int main() { //main function
	cout << "Yavuz Ucarkus 152120171006" << endl << endl;
	MAZE maze;
	maze.playGame();
}
