#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>

typedef std::vector<std::string> Grid;

bool isValidCell(const Grid& grid, const int& x, const int& y) {
    return (x >= 0 && x < (int)grid[0].size() && y >= 0 && y < (int)grid.size());
}

int countCell(const Grid& grid, const int& x, const int& y) {
    int count = 0;

    // Horiz/Vert
    if (isValidCell(grid, x - 1, y) && grid[y][x - 1] == '#') {
        ++count;
    }
    if (isValidCell(grid, x + 1, y) && grid[y][x + 1] == '#') {
        ++count;
    }
    if (isValidCell(grid, x, y - 1) && grid[y - 1][x] == '#') {
        ++count;
    }
    if (isValidCell(grid, x, y + 1) && grid[y + 1][x] == '#') {
        ++count;
    }

    // Diag
    if (isValidCell(grid, x - 1, y - 1) && grid[y - 1][x - 1] == '#') {
        ++count;
    }
    if (isValidCell(grid, x + 1, y - 1) && grid[y - 1][x + 1] == '#') {
        ++count;
    }
    if (isValidCell(grid, x + 1, y + 1) && grid[y + 1][x + 1] == '#') {
        ++count;
    }
    if (isValidCell(grid, x - 1, y + 1) && grid[y + 1][x - 1] == '#') {
        ++count;
    }

    return count;
}

void nextIter(Grid& grid) {
    Grid t(grid);
    for (int y = 0; y < (int)grid.size(); ++y) {
        for (int x = 0; x < (int)grid[0].size(); ++x) {
            if ((x == 0 && y == 0) ||
                (x == 0 && y == (int)grid.size() - 1) ||
                (x == (int)grid[0].size() - 1 && y == 0) ||
                (x == (int)grid[0].size() - 1 && y == (int)grid.size() - 1)) {
                continue;

            }

            int i = countCell(grid, x, y);;

            if (grid[y][x] == '.') {
                if (i == 3) t[y][x] = '#';
            } else if (grid[y][x] == '#') {
                if (!(i == 2 || i == 3)) t[y][x] = '.';
            }
        }
    }

    grid = t;
}

int main() {
    std::ifstream file("in");
    std::string line;
    Grid grid;

    while (getline(file, line)) {
        grid.push_back(line);
    }

    for (int i = 0; i < 100; ++i) {
        //copy(grid.begin(), grid.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
        //std::cout << std::endl;
        nextIter(grid);
    }

    int count = 0;
    for (auto e : grid) {
        for (auto i : e) {
            if (i == '#') {
                ++count;
            }
        }
    }
    std::cout << count;
}
