#include <cctype>
#include <iostream>
#include <queue>

#include "maze.hpp"

using namespace std;

TwoD::_2d_corrdinate(size_t x, size_t y)
{
	this->x = x;
	this->y = y;
}

Maze::Maze() : mapN(0), mapM(0)
{
	// initalize map
	for (size_t i = 0; i < MAX_MAP_SIZE; i++)
	{
		for (size_t j = 0; j < MAX_MAP_SIZE; j++)
		{
			map[i][j] = EMPTY;
		}
	}
}

void Maze::GetMapInput(FILE *fp)
{
	char chTemp;

	fscanf(fp, "%zu %zu", &mapN, &mapM);

	for (size_t i = 0; i < mapN; i++)
	{
		for (size_t j = 0; j < mapM; j++)
		{
			fscanf(fp, " %c", &chTemp);

			map[i][j] = chTemp - '0';
		}
	}
}

void Maze::PrintMap()
{
	for (size_t i = 0; i < mapN; i++)
	{
		if (i != 0)
		{
			putchar('\n');
		}

		for (size_t j = 0; j < mapM; j++)
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

	fflush(stdout);
}

bool Maze::IsSafeToGo(size_t xPlusOne, size_t yPlusOne)
{
	bool result = true;

	if (xPlusOne == 0 || yPlusOne == 0)
	{
		result = false;
	}
	else if (yPlusOne == mapN + 1 || xPlusOne == mapM + 1)
	{
		result = false;
	}
	else if (map[yPlusOne - 1][xPlusOne - 1] == WALL)
	{
		result = false;
	}

	return result;
}

bool Maze::IsVisited(vector<TwoD> v, size_t x, size_t y)
{
	bool isVisited = false;

	for (auto &&i : v)
	{
		if (i.x == x && i.y == y)
		{
			isVisited = true;

			break;
		}
	}

	return isVisited;
}

TwoD Maze::GetStartPos()
{
	TwoD startP;

	for (size_t i = 0; i < mapN; i++)
	{
		for (size_t j = 0; j < mapM; j++)
		{
			if (map[i][j] == START)
			{
				startP.x = j;
				startP.y = i;

				break;
			}
		}
	}

	return startP;
}

TwoD Maze::GetEndPos()
{
	TwoD endP;

	for (size_t i = 0; i < mapN; i++)
	{
		for (size_t j = 0; j < mapM; j++)
		{
			if (map[i][j] == END)
			{
				endP.x = j;
				endP.y = i;

				break;
			}
		}
	}

	return endP;
}

unsigned Maze::GetShortestPathLength()
{
	unsigned length = 0;
	queue<pair<TwoD, unsigned>> q;
	pair<TwoD, unsigned> startP, endP, currP;
	TwoD twoDTemp;
	vector<TwoD> visited;

	startP.first = GetStartPos();
	endP.first = GetEndPos();

	// push start coordinate and set cost to 1(inital value)
	q.emplace(startP.first, 1U);

	visited.push_back(startP.first);

	currP = startP;

	do
	{
		currP = q.front();
		q.pop();

		if (endP.first == currP.first)
		{
			length = currP.second;

			break;
		}

		// right
		if (IsSafeToGo((currP.first.x + 1) + 1, (currP.first.y + 1)) &&
			!IsVisited(visited, currP.first.x + 1, currP.first.y))
		{
			twoDTemp.x = currP.first.x + 1;
			twoDTemp.y = currP.first.y;

			// push new position and update cost
			q.emplace(twoDTemp, currP.second + 1);

			// check visited
			visited.push_back(twoDTemp);
		}

		// down
		if (IsSafeToGo((currP.first.x + 1), (currP.first.y + 1) + 1) &&
			!IsVisited(visited, currP.first.x, currP.first.y + 1))
		{
			twoDTemp.x = currP.first.x;
			twoDTemp.y = currP.first.y + 1;

			q.emplace(twoDTemp, currP.second + 1);
			visited.push_back(twoDTemp);
		}

		// left
		if (IsSafeToGo((currP.first.x + 1) - 1, (currP.first.y + 1)) &&
			!IsVisited(visited, currP.first.x - 1, currP.first.y))
		{
			twoDTemp.x = currP.first.x - 1;
			twoDTemp.y = currP.first.y;

			q.emplace(twoDTemp, currP.second + 1);
			visited.push_back(twoDTemp);
		}

		// up
		if (IsSafeToGo((currP.first.x + 1), (currP.first.y + 1) - 1) &&
			!IsVisited(visited, currP.first.x, currP.first.y - 1))
		{
			twoDTemp.x = currP.first.x;
			twoDTemp.y = currP.first.y - 1;

			q.emplace(twoDTemp, currP.second + 1);
			visited.push_back(twoDTemp);
		}

	} while (!q.empty());

	return length;
}

vector<TwoD> Maze::GetShortestPath()
{
	typedef struct _node
	{
		struct _node *next;
		struct _node *prev;
	} Node;

	Node nodeMap[MAX_MAP_SIZE][MAX_MAP_SIZE] = {};
	Node *curNode;

	// unsigned length = 0;
	queue<TwoD> q;
	TwoD startP, endP, currP;
	TwoD twoDTemp;
	vector<TwoD> visited;
	vector<TwoD> shortestPath;
	bool isSolved = false;

	startP = GetStartPos();
	endP = GetEndPos();

	// push start coordinate and set cost to 1(inital value)
	q.push(startP);

	visited.push_back(startP);

	currP = startP;

	do
	{
		currP = q.front();
		q.pop();

		if (endP == currP)
		{
			isSolved = true;
			break;
		}

		// right
		if (IsSafeToGo((currP.x + 1) + 1, (currP.y + 1)) &&
			!IsVisited(visited, currP.x + 1, currP.y))
		{
			twoDTemp.x = currP.x + 1;
			twoDTemp.y = currP.y;

			// push new position and update cost
			q.push(twoDTemp);

			// check visited
			visited.push_back(twoDTemp);

			if (nodeMap[twoDTemp.y][twoDTemp.x].prev == nullptr)
			{
				nodeMap[currP.y][currP.x].next =
					&nodeMap[twoDTemp.y][twoDTemp.x];
				nodeMap[twoDTemp.y][twoDTemp.x].prev =
					&nodeMap[currP.y][currP.x];
			}
		}

		// down
		if (IsSafeToGo((currP.x + 1), (currP.y + 1) + 1) &&
			!IsVisited(visited, currP.x, currP.y + 1))
		{
			twoDTemp.x = currP.x;
			twoDTemp.y = currP.y + 1;

			q.push(twoDTemp);
			visited.push_back(twoDTemp);

			if (nodeMap[twoDTemp.y][twoDTemp.x].prev == nullptr)
			{
				nodeMap[currP.y][currP.x].next =
					&nodeMap[twoDTemp.y][twoDTemp.x];
				nodeMap[twoDTemp.y][twoDTemp.x].prev =
					&nodeMap[currP.y][currP.x];
			}
		}

		// left
		if (IsSafeToGo((currP.x + 1) - 1, (currP.y + 1)) &&
			!IsVisited(visited, currP.x - 1, currP.y))
		{
			twoDTemp.x = currP.x - 1;
			twoDTemp.y = currP.y;

			q.push(twoDTemp);
			visited.push_back(twoDTemp);

			if (nodeMap[twoDTemp.y][twoDTemp.x].prev == nullptr)
			{
				nodeMap[currP.y][currP.x].next =
					&nodeMap[twoDTemp.y][twoDTemp.x];
				nodeMap[twoDTemp.y][twoDTemp.x].prev =
					&nodeMap[currP.y][currP.x];
			}
		}

		// up
		if (IsSafeToGo((currP.x + 1), (currP.y + 1) - 1) &&
			!IsVisited(visited, currP.x, currP.y - 1))
		{
			twoDTemp.x = currP.x;
			twoDTemp.y = currP.y - 1;

			q.push(twoDTemp);
			visited.push_back(twoDTemp);

			if (nodeMap[twoDTemp.y][twoDTemp.x].prev == nullptr)
			{
				nodeMap[currP.y][currP.x].next =
					&nodeMap[twoDTemp.y][twoDTemp.x];
				nodeMap[twoDTemp.y][twoDTemp.x].prev =
					&nodeMap[currP.y][currP.x];
			}
		}

	} while (!q.empty());

	if (isSolved)
	{
		curNode = &nodeMap[endP.y][endP.x];

		while (true)
		{
			curNode = curNode->prev;

			if (((size_t)((curNode - *nodeMap) / MAX_MAP_SIZE) == startP.y &&
				  (size_t)((curNode - *nodeMap) % MAX_MAP_SIZE) == startP.x))
			{
				break;
			}

			shortestPath.push_back(
				TwoD((size_t)((curNode - *nodeMap) % MAX_MAP_SIZE),
					 (size_t)((curNode - *nodeMap) / MAX_MAP_SIZE)));
		}
	}

	return shortestPath;
}

void Maze::MarkShortestPath(vector<TwoD> shortestPath)
{
	TwoD twoDTemp;

	while (!shortestPath.empty())
	{
		twoDTemp = shortestPath.back();

		map[twoDTemp.y][twoDTemp.x] = SHORTEST_PATH;

		shortestPath.pop_back();
	}
}