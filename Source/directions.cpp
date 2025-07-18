/* This file includes the directions showing all four cardinal direcitons and four diagonal directions one could go to.
 * This is used by adding directions[i][0] to a current row, and directions[i][1] to a current column.
 */
#include "directions.h"

const vector<pair<int, int>> directions = {
    {0, 1}, {1, 0}, {-1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1}
};
