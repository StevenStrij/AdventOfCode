#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <sstream>

class Reindeer {

    public:
        int speed;
        int flyTime;
        int restTime;
        std::string name;
        int points = 0;

        Reindeer(std::string n, int s, int f, int r) : speed{s}, flyTime{f}, restTime{r}, name{n} {}
        Reindeer() : Reindeer{"", 0, 0, 0} {}

        int getDist(int time) {

            int cycleTime = flyTime + restTime;
            int cycles = time / cycleTime;

            int totalDist = speed * flyTime * cycles;

            time -= cycles * cycleTime;
            if (time > flyTime) {
                time = flyTime;
            }

            totalDist += time * speed;
            return totalDist;
        }
};

int main() {
    std::ifstream file("in");
    std::string line;
    std::vector<std::string> tokens;
    std::vector<Reindeer> reindeers;


    while (getline(file, line)) {
        std::stringstream iss(line);

        tokens.clear();
        copy(std::istream_iterator<std::string>(iss),
             std::istream_iterator<std::string>(),
             std::back_inserter(tokens));

        reindeers.push_back(Reindeer{tokens[0], stoi(tokens[3]), stoi(tokens[6]), stoi(tokens[13])});
    }

    int numSeconds = 2503;
    for (int atSec = 1; atSec < numSeconds + 1; ++atSec) {
        int max = 0;
        int bestReindeerP = 0;
        int cPos = 0;
        for (auto e : reindeers) {
            int t = e.getDist(atSec);
            if (t > max) {
                max = t;
                bestReindeerP = cPos;
            }
            ++cPos;
        }
        reindeers[bestReindeerP].points += 1;
    }

    for (auto e : reindeers) {
        std::cout << e.name << " got " << e.points << std::endl;
    }
}
