#include <iostream>
#include <fstream>
#include <regex>

static const unsigned int TURN_OFF = 0;
static const unsigned int TURN_ON = 1;
static const unsigned int TOGGLE = 2;
static const int SIZE = 1000;

typedef std::vector<std::vector<int> > IntGrid;
typedef std::pair<int, int> GridPos;

void action(IntGrid& grid, const GridPos& p1, const GridPos& p2, const unsigned int& command) {
    for (int i = p1.second; i <= p2.second; ++i) {
        for (int j = p1.first ; j <= p2.first; ++j) {
            if (command == TURN_ON) {
                ++grid[i][j];
            } else if (command == TURN_OFF && grid[i][j] > 0) {
                --grid[i][j];
            } else if (command == TOGGLE) {
                grid[i][j] += 2;
            }
        }
    }
}

int main() {
    IntGrid grid(SIZE, std::vector<int>(SIZE, 0));

    std::ifstream file("in");
    std::string command;

    std::smatch match;
    std::regex exp("(turn on|turn off|toggle) (\\d+),(\\d+) through (\\d+),(\\d+)");

    std::string comm;
    std::string p1X, p1Y;
    std::string p2X, p2Y;

    unsigned int count = 0;

    while (getline(file, command)) {
        while (std::regex_search(command, match, exp)) {
            comm = match[1].str();
            p1X = match[2].str();
            p1Y = match[3].str();
            p2X = match[4].str();
            p2Y = match[5].str();

            command = match.suffix().str();
        }

        GridPos p1 = std::make_pair(stoi(p1X), stoi(p1Y));
        GridPos p2 = std::make_pair(stoi(p2X), stoi(p2Y));

        if (comm == "turn on") {
            action(grid, p1, p2, TURN_ON);
        } else if (comm == "turn off") {
            action(grid, p1, p2, TURN_OFF);
        } else if (comm == "toggle") {
            action(grid, p1, p2, TOGGLE);
        } else {
            std::cout << "Unacceptable command: " << comm << std::endl;
            return -1;
        }   
    }

    for (int i = 0; i < SIZE; ++i) { 
        for (int j = 0; j < SIZE; ++j) {
            count += grid[i][j];
        }
    }

    std::cout << count << std::endl;
}
