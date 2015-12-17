#include <iostream>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <stack>
//#include <fstream>
using namespace std;

//define size of maze, must be odd number
#define SIZE 21

//cell structure
struct Cell {
	bool visited;
	bool topWall;
	bool bottomWall;
	bool leftWall;
	bool rightWall;
	char display;
};

//declare functions
void Initialize(Cell Level[][SIZE]);
void ClearScreen();
void Redraw(Cell Level[][SIZE]); //DISPLAY
void DrawMaze(Cell Level[][SIZE], int &positionX, int &positionY, int &goalX, int & goalY);


// int main() {
// 	Cell Level[SIZE][SIZE];
// 	int positionX = 0;
// 	int positionY = 0;
// 	int goalX = 0;
// 	int goalY = 0;

// 	Initialize(Level);
// 	Redraw(Level); //DISPLAY
// 	DrawMaze(Level, positionX, positionY, goalX, goalY);

// 	return 0;
// }

//set up maze
void Initialize(Cell Level[][SIZE]) {
	for(int i = 0; i < SIZE; i++) {
		for(int j = 0; j < SIZE; j++) {
			Level[i][j].display = '*'; //DISPLAY
			Level[i][j].visited = false; //no cells visited
			Level[i][j].topWall = true; //all walls intact, no steps taken
			Level[i][j].bottomWall = true;
			Level[i][j].leftWall = true;
			Level[i][j].rightWall = true;
		}
	}
	for(int i = 1; i < SIZE-1; i++) {
		for(int j = 1; j < SIZE-1; j++) {
			//border cells have fewer walls within maze bounds
			Level[1][j].topWall = false;
			Level[SIZE-2][j].bottomWall = false;
			Level[i][1].leftWall = false;
			Level[i][SIZE-2].rightWall = false;
		} 
	}
}

void ClearScreen() {
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}

void Redraw(Cell Level[][SIZE]) {
	for(int i = 0; i < SIZE; i++) {
		cout << endl;
		for(int j = 0; j < SIZE; j++)
			cout << " " << Level[i][j].display;
	}
}

//generate the maze
void DrawMaze(Cell Level[][SIZE], int &positionX, int &positionY, int &goalX, int &goalY) {
	srand((unsigned)time(NULL)); //pick a random cell to start in
	int random = 0;
	int randomX = ((2*rand())+1)%(SIZE-1); //generate random odd number between 1 and size
	int randomY = ((2*rand())+1)%(SIZE-1);
	positionX = randomX; //set random numbers as start place
	positionY = randomY;
	int visitedCells = 1;
	int totalCells = ((SIZE-1)/2)*((SIZE-1)/2);
	int percent = 0;
	stack<int> backTrackX, backTrackY; //need stack to trace the reverse path

	Level[randomY][randomX].display = 'S'; //mark start cell with an S //DISPLAY
	Level[randomY][randomX].visited = true; //mark start cell as visited

	while(visitedCells < totalCells) {
		if(((Level[randomY-2][randomX].visited == false) && (Level[randomY][randomX].topWall == true && Level[randomY-2][randomX].bottomWall == true)) ||
		   ((Level[randomY+2][randomX].visited == false) && (Level[randomY][randomX].bottomWall == true && Level[randomY+2][randomX].topWall == true)) ||
		   ((Level[randomY][randomX-2].visited == false) && (Level[randomY][randomX].leftWall == true && Level[randomY][randomX-2].rightWall == true)) ||
		   ((Level[randomY][randomX+2].visited == false) && (Level[randomY][randomX].rightWall == true && Level[randomY][randomX+2].leftWall == true))) 
		{
			random = (rand() % 4) + 1; //pick wall in random direction to knock down

			//choose upper wall
			if((random == 1) && (randomY > 1)) {
				if(Level[randomY-2][randomX].visited == false) { //if cell not visited
					Level[randomY-1][randomX].display = ' '; //delete display //DISPLAY
					Level[randomY-1][randomX].visited = true; //change cell status to visited
					Level[randomY][randomX].topWall = false; //knock down top wall

					backTrackX.push(randomX); //push x for back track
					backTrackY.push(randomY); //push y for back track

					randomY -= 2; //move to next cell
					Level[randomY][randomX].visited = true; //mark cell moved to as visited
					Level[randomY][randomX].display = ' '; //delete display //DISPLAY
					Level[randomY][randomX].bottomWall = false; //knock down wall
					visitedCells++; //increase visited cells counter
				}
				else
					continue;
			}

			//choose lower wall
			else if((random == 2) && (randomY < SIZE-2)) {
				if(Level[randomY+2][randomX].visited == false) { //if cell not visited
					Level[randomY+1][randomX].display = ' '; //delete display //DISPLAY
					Level[randomY+1][randomX].visited = true; //change cell status to visited
					Level[randomY][randomX].bottomWall = false; //knock down bottom wall

					backTrackX.push(randomX); //push x for back track
					backTrackY.push(randomY); //push y for back track

					randomY += 2; //move to next cell
					Level[randomY][randomX].visited = true; //mark cell moved to as visited
					Level[randomY][randomX].display = ' '; //delete display //DISPLAY
					Level[randomY][randomX].topWall = false; //knock down wall
					visitedCells++; //increase visited cells counter
				}
				else
					continue;
			}

			//choose left wall
			else if((random == 3) && (randomX > 1)) {
				if(Level[randomY][randomX-2].visited == false) { //if cell not visited
					Level[randomY][randomX-1].display = ' '; //delete display //DISPLAY
					Level[randomY][randomX-1].visited = true; //change cell status to visited
					Level[randomY][randomX].leftWall = false; //knock down left wall

					backTrackX.push(randomX); //push x for back track
					backTrackY.push(randomY); //push y for back track

					randomX -= 2; //move to next cell
					Level[randomY][randomX].visited = true; //mark cell moved to as visited
					Level[randomY][randomX].display = ' '; //delete display //DISPLAY
					Level[randomY][randomX].rightWall = false; //knock down wall
					visitedCells++; //increase visited cells counter
				}
				else
					continue;
			}

			//choose right wall
			else if((random == 4) && (randomX < SIZE-2)) {
				if(Level[randomY][randomX+2].visited == false) { //if cell not visited
					Level[randomY][randomX+1].display = ' '; //delete display //DISPLAY
					Level[randomY][randomX+1].visited = true; //change cell status to visited
					Level[randomY][randomX].rightWall = false; //knock down right wall

					backTrackX.push(randomX); //push x for back track
					backTrackY.push(randomY); //push y for back track

					randomX += 2; //move to next cell
					Level[randomY][randomX].visited = true; //mark cell moved to as visited
					Level[randomY][randomX].display = ' '; //delete display //DISPLAY
					Level[randomY][randomX].leftWall = false; //knock down wall
					visitedCells++; //increase visited cells counter
				}
				else
					continue;
			}

			percent = (visitedCells*100/totalCells*100)/100; // progress in percentage
			cout << endl << "	Generating a Random Maze... " << percent << "%" << endl;
		}

		else {
			randomX = backTrackX.top();
			backTrackX.pop();

			randomY = backTrackY.top();
			backTrackY.pop();
		}

		ClearScreen();
		//Redraw(Level);
	}

	goalX = randomX;
	goalY = randomY;
	Level[goalY][goalX].display = 'E';
	system("cls");
	ClearScreen();
	Redraw(Level);
	cout << endl << "\a\t	Complete!" << endl;
}