#pragma once
#include <vector>
#include <stdexcept>
#include <sstream>
#include <iostream>
using namespace std;

template <typename ValueType>
class Grid {
public:
    Grid();
    Grid(int nRows, int nCols);
    Grid(int nRows, int nCols, ValueType value);

    int numRows() const;
    int numCols() const;
    int size() const;
    bool inBounds(int row, int col) const;
    bool isEmpty() const;

    ValueType get(int row, int col) const;
    void set(int row, int col, ValueType value);
    void fill(ValueType value);
    void resize(int nRows, int nCols);
    void clear();

    string toString() const;
    string toString2D() const;

    vector<ValueType>& operator[](int row);
    const vector<ValueType>& operator[](int row) const;

private:
    vector<vector<ValueType>> elements;
};

