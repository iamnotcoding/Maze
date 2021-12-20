#include <iostream>

#include "maze.hpp"

using namespace std;

Maze::Maze() : mapSize(0)
{
    // initalize map
    for (size_t i = 0; i < mapSize; i++)
    {
        for (size_t j = 0; j < mapSize; j++)
        {
            map[i][j] = EMPTY;
        }
    }
}

void Maze::GetMapInput(size_t n, FILE *fp)
{
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			fscanf(fp, "%hhu", &map[i][j]);
		}
	}

	mapSize = n;
}

void Maze::PrintMap()
{
	for (size_t i = 0; i < mapSize; i++)
	{
		if (i != 0)
		{
			putchar('\n');
		}

		for (size_t j = 0; j < mapSize; j++)
		{
			if (j != 0)
			{
				putchar(' ');
			}

			if (map[i][j] == PATH)
			{
				putchar('+');
			}
			else if (map[i][j] == WALL)
			{
				putchar('#');
			}
			else if (map[i][j] == START)
			{
				putchar('s');
			}
			else if (map[i][j] == END)
			{
				putchar('e');
			}
			else if (map[i][j] == SHORTEST_PATH)
			{
				putchar('*');
			}
			else
			{
				putchar('?');
			}
		}
	}
}

unsigned Maze::GetShortestPathLength()
{
	unsigned length;

	typedef struct _node
	{
		struct _node *next;
		struct _node *prev;

		unsigned count = 0;
	} Node;
}