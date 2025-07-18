/* This is the Breadth First Search implementation file in cpp. I edited the function to only search 5 at a 
 * time so it's slowed down. This way, we can see how the function searches for the shortest pathin a grid by searching always 
 * checking the nearested unvisited cell from the start.
 */
#include "grid.h"
#include "bfs.h"
#include <queue>
#include <vector>
#include <utility> // using for pair
#include <map>
#include "directions.h"
#include "CellType.h"

queue<pair<int,int>> bfsNeighbors;
map<pair<int,int>, pair<int,int>> bfsParents;
bool bfsFound = false;

int visitedCount = 0;
int pathCount = 0;

/* This initializes the funciton and is called in main.cpp everytime the BFS button is clicked.
 * Ensures the queue and map are empty, and target has not been found yet. Takes in the represented grid
 * and ints startRow and startCol which represent where the starting cell is.
 */
void bfsInit(Grid<int>& grid, int startRow, int startCol) {
    while (!bfsNeighbors.empty()) bfsNeighbors.pop();
    bfsParents.clear();
    bfsFound = false;
    bfsNeighbors.push({startRow, startCol});
}

/* Helper funcation that determines whether or not a nearby coordinate in the grid is a diagonal 
 * of the current cell. Takes in row and col as ints which represent how much to add to the current cell to get the 
 * nearby cell.
 */
bool isDiagonal(int row, int col) {
    return (abs(row) + abs(col)) == 2;
}

/* Returns true if a move is valid, false if otherwise. Takes in the grid of integers and a row and column to check as integers.
 * dr and dc are the directions of a row and column that we are now going to check. This is used to calculate the new cell we 
 * are checking.
 */
bool isValid(Grid<int>& grid, int row, int col, int dr, int dc) {
    int newRow = row + dr;
    int newCol = col + dc;
    if (!grid.inBounds(newRow, newCol)) return false;
    if (grid.get(newRow, newCol) == WALL) return false;
    if (isDiagonal(dr, dc)) {
        int adj1R = newRow;
        int adj1C = col;
        int adj2R = row;
        int adj2C = newCol;
        if ((grid.get(adj1R, adj1C) == WALL ) || (grid.get(adj2R, adj2C) == WALL)) return false;
    }
    return true;
}

/* The bfs implements the breadth first search algorithm to find the shortest path to the cell that is 
 * marked with FINISH. The function only checks 5 cells at time so we can see the slow visual. This takes in 
 * a grid of integers, and the start row (startRow) and start column (startCol) as integers.
 */
bool bfs(Grid<int>& grid, int startRow, int startCol) {
    if (bfsNeighbors.empty()) return true;
    // How many cells are checked per frame.
    int fps = 5;
    while (fps-- > 0 && !bfsNeighbors.empty()) {
        auto position = bfsNeighbors.front();
        bfsNeighbors.pop();
        // four cardinal directions + four diagonal directions.
        for (auto [dr, dc] : directions) {
            int newRow = position.first + dr;
            int newCol = position.second + dc;

            if (isValid(grid, position.first, position.second, dr, dc)) {
                if (grid.get(newRow, newCol) == EMPTY) {
                    grid.set(newRow, newCol, VISITED);
                    // set where it came from so we can backtrack
                    bfsParents[{newRow, newCol}] = position;
                    bfsNeighbors.push({newRow, newCol});
                    visitedCount++;
                } else if (grid.get(newRow, newCol) == FINISH) {
                    bfsParents[{newRow, newCol}] = position;
                    bfsFound = true;
                    return true;
                }
            }   
        }
    }
    return false;
}

/* This function preforms the backtracking, taking in the grid of integers to mark the path, the original start and the finish
 * as integers of rows and columns. Since we know that the parents of the cell that first hit the finish is the quickest path,
 * we can just park the parents of that finishing cell.
 */
void bfsBacktrackPath(Grid<int>& grid, int startRow, int startCol, int endRow, int endCol) {
    if (!bfsFound) return;
    pair<int, int> curr = {endRow, endCol};
    while (curr != make_pair(startRow, startCol)) {
        curr = bfsParents[curr];
        if (curr != make_pair(startRow, startCol)) {
            grid.set(curr.first, curr.second, PATH);
            pathCount++;
        }
    }
}