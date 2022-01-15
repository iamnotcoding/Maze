#include <iostream>
#include <string>

#include "maze.hpp"

#define DATA_FILE_NAME "maze.txt"

using namespace std;

int main()
{
	FILE *input;
	Maze maze;
	unsigned length;
	vector<TwoD> shortestPath;

	input = fopen(DATA_FILE_NAME, "r");

	if (input == NULL)
	{
		perror("Cannot open file " DATA_FILE_NAME " ");

		return 1;
	}

	maze.GetMapInput(input);

	maze.PrintMap();

	putchar('\n');

	length = maze.GetShortestPathLength();

	cout << "path length : " << length << endl;

	shortestPath = maze.GetShortestPath();

	maze.MarkShortestPath(shortestPath);
	
	maze.PrintMap();
}
