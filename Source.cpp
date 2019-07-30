#include <iostream>
#include <fstream>
#include <string>
using namespace std;
const char Wall = '#';		//For maze
const char Free = '.';		//For maze


void stringPermute(string str, int n);
int primeTest(int n, int nMinus);
bool solution(char Maze[][101], char mazePos[][101], int goalX, int goalY, int y, int x);

int main()
{
	int a, b;
	string str1, str2;
	int str1Lngth, str2Lngth; //# of characters in a string
	int nP, nP2, nP3, nP4, nP5;
	int npMinus, np2Minus, np3Minus, np4Minus, np5Minus; //dividens
	int dimR, dimC;
	int startR, startC;
	int y, x;			//y will hold startR, and x will hold startC.
	int goalR, goalC;
	char maze[100][100 + 1];
	char mazePos[100][100 + 1];	//this will hold the previous move made in the maze
								//to prevent going back and forth infintely.
	ifstream File;
	File.open("ola3data.txt");
	File >> a >> str1 >> str2 >> b >> nP >> nP2 >> nP3 >> nP4 >> nP5 >> dimR >> dimC >> startR >> startC >> goalR >> goalC;
	for (int i = 0; i < dimR; i++)	//loop once for each row
	{
		for (int j = 0; j < dimC; j++)	//loop once for each column
		{
			File >> maze[i][j];			//intialize maze as a matrix
		}//end of for i
	}//end of for j
	File.close();

	str1Lngth = str1.size();
	str2Lngth = str2.size();
	stringPermute(str1, str1Lngth);
	cout << endl;
	stringPermute(str2, str2Lngth);
	cout << endl;

	npMinus = nP - 1;
	np2Minus = nP2 - 1;
	np3Minus = nP3 - 1;
	np4Minus = nP4 - 1;
	np5Minus = nP5 - 1;

	primeTest(nP, npMinus);
	cout << endl;
	//
	cout << endl;
	primeTest(nP2, np2Minus);
	cout << endl;
	primeTest(nP3, np3Minus);
	cout << endl;
	primeTest(nP4, np4Minus);
	cout << endl;
	primeTest(nP5, np5Minus);
	cout << endl;
	y = startR;
	x = startC;

	solution(maze, mazePos, goalC, goalR, y, x);
	system("PAUSE");
	return 0;
}

void stringPermute(string str, int n)
{


	//int p = n;



	if (n == 1)			//After x swaps (where x = length of string - 1) display string
	{
		cout << str << endl;
	}

	else {
		for (int i = 0; i < n; i++) {
			stringPermute(str, n - 1);			//recursive call

			if ((n % 2 == 0))			//if n is even swap element i with element (n - 1)
			{
				swap(str[i], str[(n - 1)]);
			}
			else						//else n is odd so swap the first element with element (n - 1) 
			{
				swap(str[0], str[n - 1]);
			}
		}//end of for
	}//end of else
}

int primeTest(int n, int nMinus)
{
	//	cout << "In primeTest!\n";
	int num = n;
	int numMinus = nMinus;
	if (numMinus != 0)
	{
		if (num % numMinus == 0 && numMinus != 1) //not a prime number
		{
			int quotient = num / numMinus;
			cout << num << " is not a prime number.\n";
			cout << num << " can be divided by, at least, " << numMinus;
			cout << " with a quotient of " << quotient << ".\n";

			return 1;
		}
		else if (numMinus == 1)
		{
			cout << num << " is a prime number.\n";
			return 1;
		}
		else {											//else num % numMinus != 0

			primeTest(num, (numMinus - 1));					//decrement numMinus in recursive call
		}

	}//end if numMinus != 0
	else if (num == 1 && numMinus == 0)
	{
		cout << "1 is not prime.\n";
	}
}

bool solution(char Maze[][101], char mazePos[][101], int goalX, int goalY, int y, int x)
{

	cout << "Moving from row: " << y << " and column: " << x << ".\n";	//displaying forward path

																		//check for goal
	if ((x == goalX) && (y == goalY)) {
		cout << "At goal of row: " << goalY << " and column: " << goalX << endl;
		return true;

	}
	//check for invalid position 
	if ((x == 0) || (y == 0))
	{
		return false;
	}

	Maze[y][x] = mazePos[y][x];	//mazePos holds the position that the program just left

								//(Below) Move North- If X is below 100, and the westward position is a valid path...
								//and the program did not just come from that position, move north.
	if (y >= 1 && Maze[y - 1][x] == Free && Maze[y - 1][x] != mazePos[y][x] && solution(Maze, mazePos, goalX, goalY, y - 1, x)) { //check north

																																  //	cout << "Checking North.\n";
		return true;

	}
	//(Below) Move East- If X is below 100, and the eastward position is a valid path...
	//and the program did not just come from that position, move east.
	if (x <= 100 && Maze[y][x + 1] == Free && Maze[y][x + 1] != mazePos[y][x] && solution(Maze, mazePos, goalX, goalY, y, x + 1)) //east
	{

		return true;
	}
	//(Below) Move south- If y is below 100, and the southward position is a valid path...
	//and the program did not just come from that position, move south.
	if ((y < 100) && Maze[y + 1][x] == Free && Maze[y + 1][x] != mazePos[y][x] && solution(Maze, mazePos, goalX, goalY, y + 1, x)) { //south
																																	 //		cout << "Checking south.\n";

		return true;

	}
	//(Below) Move west - If X is below 100, and the westward position is a valid path...
	//and the program did not just come from that position, move west.
	if (x <= 100 && Maze[y][x - 1] == Free && Maze[y][x - 1] != mazePos[y][x] && solution(Maze, mazePos, goalX, goalY, y, x - 1)) //west
	{

		return true;
	}


	cout << "Backtracking from row: " << y << " and column: " << x << ".\n"; //displaying back path

	return false;

}