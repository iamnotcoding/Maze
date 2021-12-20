#ifndef MAZE_HPP
#define MAZE_HPP

#include <iostream>

#define MAP_SIZE 100

#define PATH 0
#define WALL 1
#define START 2
#define END 3
#define SHORTEST_PATH 4
#define EMPTY 5 // treated as an error

class Maze
{
  private:
	unsigned char map[MAP_SIZE][MAP_SIZE];
	size_t mapSize;

  public:
	// constructer
	Maze();

	void GetMapInput(size_t n, FILE *fp);
	void PrintMap(void);
    bool IsSafeToGo(size_t x, size_t y);
	// with bfs
	unsigned GetShortestPathLength(void);
	// with bfs
	void PrintShortestPath(void);
};

#endif