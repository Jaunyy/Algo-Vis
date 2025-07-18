/* This file implements the functionality of grid attributes.
 * Although I haven't used all of these functions in my algorithm implemenetations, 
 * I created them thinking they will be useful in the future.
 */
#include "grid.h"
#include <vector>
using namespace std;

template class Grid<int>;

template <typename ValueType>
Grid<ValueType>::Grid() { }

template <typename ValueType>
Grid<ValueType>::Grid(int nRows, int nCols) {
    resize(nRows, nCols);
}

template <typename ValueType>
Grid<ValueType>::Grid(int nRows, int nCols, ValueType value) {
    resize(nRows, nCols);
    fill(value);
}

template <typename ValueType>
int Grid<ValueType>::numRows() const {
    return elements.size();
}

template <typename ValueType>
int Grid<ValueType>::numCols() const {
    return elements.empty() ? 0 : elements[0].size();
}

template <typename ValueType>
int Grid<ValueType>::size() const {
    return numRows() * numCols();
}

template <typename ValueType>
bool Grid<ValueType>::inBounds(int row, int col) const {
    return row >= 0 && row < numRows() && col >= 0 && col < numCols();
}

template <typename ValueType>
bool Grid<ValueType>::isEmpty() const {
    return size() == 0;
}

template <typename ValueType>
ValueType Grid<ValueType>::get(int row, int col) const {
    if (!inBounds(row, col)) throw out_of_range("Grid::get - index out of bounds");
    return elements[row][col];
}

template <typename ValueType>
void Grid<ValueType>::set(int row, int col, ValueType value) {
    if (!inBounds(row, col)) throw out_of_range("Grid::set - index out of bounds");
    elements[row][col] = value;
}

template <typename ValueType>
void Grid<ValueType>::fill(ValueType value) {
    for (auto& row : elements)
        std::fill(row.begin(), row.end(), value);
}

template <typename ValueType>
void Grid<ValueType>::clear() {
    elements.clear();
}

template <typename ValueType>
void Grid<ValueType>::resize(int nRows, int nCols) {
    elements.resize(nRows);
    for (auto& row : elements)
        row.resize(nCols);
}

template <typename ValueType>
std::vector<ValueType>& Grid<ValueType>::operator[](int row) {
    if (row < 0 || row >= numRows()) throw std::out_of_range("Grid::operator[] - row index out of bounds");
    return elements[row];
}

template <typename ValueType>
const std::vector<ValueType>& Grid<ValueType>::operator[](int row) const {
    if (row < 0 || row >= numRows()) throw std::out_of_range("Grid::operator[] - row index out of bounds");
    return elements[row];
}

