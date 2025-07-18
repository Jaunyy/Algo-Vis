#pragma once
#include <queue>
#include <map>
#include <utility>

extern int visitedCount;
extern int pathCount;

void bfsInit(Grid<int>& grid, int startRow, int startCol);
bool bfs(Grid<int>& grid, int endRow, int endCol);
void bfsBacktrackPath(Grid<int>& grid, int startRow, int startCol, int endRow, int endCol);
