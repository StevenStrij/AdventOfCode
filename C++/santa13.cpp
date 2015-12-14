#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <iterator>
#include <algorithm>

typedef std::map<std::pair<std::string, std::string>, int> HappinessRatings;

int calculateTable(const std::vector<std::string>& seats, HappinessRatings& hp) {

    int happiness = 0;
    for (int i = 0; i < 9; ++i) {
        int t1, t2;
        if (i == 0) {
            t1 = 8;
        } else {
            t1 = i - 1;
        }

        if (i == 8) {
            t2 = 0;
        } else {
            t2 = i + 1;
        }

        happiness += hp[std::make_pair(seats[i], seats[t1])];
        happiness += hp[std::make_pair(seats[i], seats[t2])];
    }

    return happiness;
}

int getMax(std::vector<std::string> avail, 
           std::vector<std::string> seats, HappinessRatings& hp) {

    if (seats.size() == 9) {
        return calculateTable(seats, hp);
    }

    int max = -999999;
    for (unsigned long t = 0; t < avail.size(); ++t) {
        std::vector<std::string> availT = avail;
        std::vector<std::string> seatsT = seats;

        seatsT.push_back(avail[t]);
        availT.erase(availT.begin() + t);
        max = std::max(max, getMax(availT, seatsT, hp));
    }

    return max;
}

int main() {
    std::ifstream file("in");
    std::string line;
    std::vector<std::string> tokens;

    HappinessRatings pairs;
    std::vector<std::string> people{};

    while (getline(file, line)) {
        tokens.clear();
        std::stringstream iss(line);

        copy(std::istream_iterator<std::string>(iss),
             std::istream_iterator<std::string>(),
             std::back_inserter(tokens));

        tokens[10].erase(tokens[10].begin() + tokens[10].size() - 1);
        
        if (tokens[2] == "lose") {
            pairs[std::make_pair(tokens[0], tokens[10])] = -stoi(tokens[3]);
        } else {
            pairs[std::make_pair(tokens[0], tokens[10])] = stoi(tokens[3]);
        }   

        if (std::find(people.begin(), people.end(), tokens[0]) == people.end()) {
            people.push_back(tokens[0]);
        }
    }

    std::cout << "People are: " << std::endl;
    copy(people.begin(), people.end(), std::ostream_iterator<std::string>(std::cout, ", "));
    std::cout << std::endl;
    std::cout << getMax(people, std::vector<std::string>{}, pairs) << std::endl;
}
