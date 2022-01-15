#ifndef MAZE_HPP
#define MAZE_HPP

#include <iostream>
#include <vector>

#define MAX_MAP_SIZE 100

#define WALL 0
#define PATH 1
#define START 2
#define END 3
#define SHORTEST_PATH 4
#define EMPTY 5 // treated as an error

using namespace std;

typedef struct _2d_corrdinate
{
	size_t x;
	size_t y;

	_2d_corrdinate() = default;
	_2d_corrdinate(size_t x, size_t y);

	bool operator==(const struct _2d_corrdinate &other) const
	{
		return x == other.x && y == other.y;
	}

	bool operator!=(const struct _2d_corrdinate &other) const
	{
		return x != other.x || y != other.y;
	}
} TwoD;

class Maze
{
  private:
	unsigned char map[MAX_MAP_SIZE][MAX_MAP_SIZE];
	size_t mapN;
	size_t mapM;

	bool IsSafeToGo(size_t x, size_t y);
	bool IsVisited(vector<TwoD> v, size_t x, size_t y);
	TwoD GetStartPos();
	TwoD GetEndPos();

  public:
	// constructer
	Maze();
	void GetMapInput(FILE *fp);
	void PrintMap(void);
	// with bfs
	unsigned GetShortestPathLength(void);
	// with bfs, path is stored reversely
	vector<TwoD> GetShortestPath();

	void MarkShortestPath(const vector<TwoD> sPath);
};

#endif