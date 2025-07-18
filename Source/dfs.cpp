/* This file uses the depth first search algorithm to find a path to the finishing cell recursively.
 * The nature of this algorithm doesn't allow for the quickest path to the finish, but I implemented this 
 * to show its sporatic behavior in finding the finish. I could not come up with slowing this algorithm down 
 * by the frames because this was implemented recursively.
 */
#include "grid.h"
#include "dfs.h"
#include <vector>
#include <utility> // for std::pair
#include "directions.h"
#include "bfs.h"    // for visited & path count
#include "CellType.h"

int n = directions.size();

/* This function takes in the grid of integers, a start and finish column represented as rows and cols as integers.
 * This implementation is recursive, marking every visited path as VISITED, and only going after the next EMPTY cell.
 * It returns true if the path was found, and returns false otherwise. 
 */
bool dfs(Grid<int>& grid, int startRow, int startCol, int endRow, int endCol) {
    if (!grid.inBounds(startRow, startCol)) return false;
    int cell = grid.get(startRow, startCol);
    if (cell == WALL || cell == VISITED || cell == PATH) return false;
    if (startRow == endRow && startCol == endCol) return true;
    // after base cases, if empty, mark as visited.
    if (cell != START && cell != FINISH) {
        grid.set(startRow, startCol, VISITED);
        visitedCount++;
    }
    for (auto [dr, dc] : directions) {
        int newRow = startRow + dr;
        int newCol = startCol + dc;
        // recursive call with the new cell.
        if (dfs(grid, newRow, newCol, endRow, endCol)) {
            if (cell != START && cell != FINISH)
                grid.set(startRow, startCol, PATH);
                pathCount++;
                return true;
            }
        }
        
    return false;
}