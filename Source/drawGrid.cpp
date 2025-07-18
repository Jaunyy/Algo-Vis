/* This file is mainly used to draw a grid of a specified row and column numbers.
 * This also holds the coloring for every type a cell can be. Only called in main.cpp.
 */

#include "drawGrid.h"
#include "CellType.h"

sf::Color cellColor(int value) {
    switch (value) {
        case 1: return sf::Color::Green;      // START
        case 2: return sf::Color::Red;       // FINISH
        case 3: return sf::Color::Black;     // WALL
        case 4: return sf::Color(100, 100, 100); // VISITED (grayish)
        case 5: return sf::Color::Yellow;    // PATH ✅
        default: return sf::Color::White;    // EMPTY
    }
}

/* drawGrid draws the grid and colors each cell with it's type, given it's value. The grid of ints is given, and a cell width and height
 * and uses a double for loop to draw each cell.
 */
void drawGrid(const Grid<int>& grid, sf::RenderTarget& target, float cellWidth, float cellHeight) {
    for (int r = 0; r < grid.numRows(); ++r) {
        for (int c = 0; c < grid.numCols(); ++c) {
            // minus one to see lines. 
            sf::RectangleShape rect(sf::Vector2f(cellWidth - 1, cellHeight - 1));   
            rect.setPosition(c * cellWidth, r * cellHeight);
            rect.setFillColor(cellColor(grid.get(r, c)));
            rect.setOutlineThickness(1.0f); // 1 pixel wide border
            rect.setOutlineColor(sf::Color(50, 50, 50)); // dark gray
            target.draw(rect);
        }
    }
}
