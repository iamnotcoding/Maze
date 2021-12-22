#ifndef MAZE_HPP
#define MAZE_HPP

#include <iostream>

#define MAX_MAP_SIZE 100

#define PATH 0
#define WALL 1
#define START 2
#define END 3
#define SHORTEST_PATH 4
#define EMPTY 5 // treated as an error

typedef struct _2d_corrdinate
{
	size_t x;
	size_t y;

	bool operator==(const struct _2d_corrdinate &other) const
	{
		return x == other.x && y == other.y;
	}
} TwoD;

class Maze
{
  private:
	unsigned char map[MAX_MAP_SIZE][MAX_MAP_SIZE];
	size_t mapSize;

	bool IsSafeToGo(size_t x, size_t y);
	TwoD GetStartPos();
	TwoD GetEndPos();

  public:
	// constructer
	Maze();
	void GetMapInput(size_t n, FILE *fp);
	void PrintMap(void);
	// with bfs
	unsigned GetShortestPathLength(void);
	// with bfs
	void PrintShortestPath(void);
};

#endif