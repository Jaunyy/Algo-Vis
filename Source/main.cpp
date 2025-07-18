/* This file creates the window using SFML graphics and draws the grid using drawGrid.cpp.
 * A user is able to draw and remove walls in this grid, calling upon either the BFS or DFS button
 * to find a path from the chosen start cell, to the chosen finish cell. 
 */
#include <SFML/Graphics.hpp>
#include "grid.h"
#include "drawGrid.h"
#include "dfs.h"
#include "bfs.h"
#include "CellType.h"

const int rows = 70;
const int cols = 70;
bool drawing = false;
int initialCell = 0;
bool dfsRun = false;
bool bfsRun = false;
bool bfsRunning = false;

// Creates space for the buttons.
sf::FloatRect runDFSButtonBounds, resetButtonBounds, runBFSButtonBounds;

enum PlacementMode {
    PLACING_START,
    PLACING_FINISH,
    PLACING_WALLS
};

PlacementMode mode = PLACING_START;
sf::Vector2i startPos(-1, -1);
sf::Vector2i finishPos(-1, -1);

int main() {

    // Saves room for the buttons and statistics at the bottom fo the window.
    const int uiPanelHeight = 100;
    sf::RenderWindow window(
        sf::VideoMode(700, 700 + uiPanelHeight),
        "Pathfinding Visualizer",
        sf::Style::Default
    );

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1; 
    }

    Grid<int> grid(rows, cols, EMPTY);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);
                // if DFS button is run, call DFS function and continue the loop.
                if (runDFSButtonBounds.contains(mouse) && mode == PLACING_WALLS && !dfsRun && !bfsRun) {
                    dfs(grid, startPos.y, startPos.x, finishPos.y, finishPos.x);
                    dfsRun = true;
                    continue;
                // if reset button is clicked, reset all flags, and clear the grid.
                } else if (resetButtonBounds.contains(mouse)) {
                    grid.fill(EMPTY);
                    startPos = {-1, -1};
                    finishPos = {-1, -1};
                    mode = PLACING_START;
                    dfsRun = false;
                    bfsRun = false; 
                    bfsRunning = false;
                    visitedCount = 0;
                    pathCount = 0;
                    continue;
                // if BFS button is clicked, initialize bfs and turn on the bfs running flags.
                } else if (runBFSButtonBounds.contains(mouse) && mode == PLACING_WALLS && !bfsRun && !dfsRun) {
                    bfsInit(grid, startPos.y, startPos.x);
                    bfsRun = true;
                    bfsRunning = true;
                    continue;
                } 
                int gx = event.mouseButton.x * cols / window.getSize().x;
                int gy = event.mouseButton.y * rows / (window.getSize().y - uiPanelHeight);
                if (!grid.inBounds(gy, gx) || event.mouseButton.y > (window.getSize().y - uiPanelHeight))
                    continue;
                // Determines what to do if user is drawing walls or placing starting or finishing cell.
                switch (mode) {
                    case PLACING_START:
                        if (grid.get(gy, gx) == EMPTY) {
                            grid.set(gy, gx, START);
                            startPos = { gx, gy };
                            mode = PLACING_FINISH;
                        }
                        break;
                    case PLACING_FINISH:
                        if (grid.get(gy, gx) == EMPTY) {
                            grid.set(gy, gx, FINISH);
                            finishPos = { gx, gy };
                            mode = PLACING_WALLS;
                        }
                        break;
                    case PLACING_WALLS:
                        drawing = true;
                        initialCell = grid.get(gy, gx);
                        break;
                }
            } else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                drawing = false;
            }
        }
        
        // if BFS was run, update bfs by the fps in the function. This will stop when finish has been found or all cells have been checked.
        if (bfsRunning) {
            bool done = bfs(grid, finishPos.y, finishPos.x);
            if (done) {
                bfsBacktrackPath(grid, startPos.y, startPos.x, finishPos.y, finishPos.x);
                bfsRunning = false;
            }
        }

        float gridHeight = window.getSize().y - uiPanelHeight;
        float cellWidth = static_cast<float>(window.getSize().x) / cols;
        float cellHeight = gridHeight / rows;

        // Draws the walls and accounts for drag.
        if (drawing && mode == PLACING_WALLS) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            int gx = mousePos.x * cols / window.getSize().x;
            int gy = mousePos.y * rows / gridHeight;
            if (grid.inBounds(gy, gx)) {
                int current = grid.get(gy, gx);
                if (current == EMPTY && initialCell == EMPTY) {
                    grid.set(gy, gx, WALL);
                } else if (current == WALL && initialCell == WALL) {
                    grid.set(gy, gx, EMPTY);
                }
            }
        }

        window.clear(sf::Color::Black);
        drawGrid(grid, window, cellWidth, cellHeight);

        // UI panel background
        sf::RectangleShape uiPanel(sf::Vector2f(window.getSize().x, uiPanelHeight));
        uiPanel.setPosition(0, gridHeight);
        uiPanel.setFillColor(sf::Color(40, 40, 40));
        window.draw(uiPanel);

        // Run DFS Button
        sf::RectangleShape runButton(sf::Vector2f(100, 40));
        runButton.setPosition(20, gridHeight + 30);
        runButton.setFillColor(sf::Color(100, 200, 100));
        runDFSButtonBounds = runButton.getGlobalBounds();
        window.draw(runButton);

        sf::Text runText("Run DFS", font, 16);
        runText.setPosition(runButton.getPosition().x + 15, runButton.getPosition().y + 10);
        runText.setFillColor(sf::Color::Black);
        window.draw(runText);

        // Reset Button
        sf::RectangleShape reset(sf::Vector2f(100, 40));
        reset.setPosition(140, gridHeight + 30);
        reset.setFillColor(sf::Color(200, 100, 100));
        resetButtonBounds = reset.getGlobalBounds();
        window.draw(reset);

        sf::Text resetText("Reset", font, 16);
        resetText.setPosition(reset.getPosition().x + 20, reset.getPosition().y + 10);
        resetText.setFillColor(sf::Color::Black);
        window.draw(resetText);

        // Run BFS Button
        sf::RectangleShape runBFS(sf::Vector2f(100, 40));
        runBFS.setPosition(260, gridHeight + 30);
        runBFS.setFillColor(sf::Color(100, 200, 100));
        runBFSButtonBounds = runBFS.getGlobalBounds();
        window.draw(runBFS);

        sf::Text runBFSText("Run BFS", font, 16);
        runBFSText.setPosition(runBFS.getPosition().x + 15, runBFS.getPosition().y + 10);
        runBFSText.setFillColor(sf::Color::Black);
        window.draw(runBFSText);

        // Stats 
        sf::Text stats;
        stats.setFont(font);
        stats.setCharacterSize(16);
        stats.setFillColor(sf::Color::White);
        stats.setPosition(450, window.getSize().y - 60);
        stats.setString("Visited: " + std::to_string(visitedCount) + "  Path: " + std::to_string(pathCount));
        window.draw(stats);

        window.display();
    }
    return 0;
}