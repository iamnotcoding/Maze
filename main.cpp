#include <iostream>
#include <string>

#include "maze.hpp"

#define DATA_FILE_NAME "maze.txt"
using namespace std;

int main()
{
	FILE *input;
        Maze maze;
        
        input = fopen(DATA_FILE_NAME, "r");

        if (input == NULL)
        {
                perror("Cannot open file " DATA_FILE_NAME " ");
                return 1;
        }

        maze.GetMapInput(5, input);
        
        maze.PrintMap();
}
