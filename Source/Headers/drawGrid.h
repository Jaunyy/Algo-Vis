#pragma once
#include <SFML/Graphics.hpp>
#include "grid.h"

void drawGrid(const Grid<int>& grid, sf::RenderTarget& target, float cellWidth, float cellHeight);
