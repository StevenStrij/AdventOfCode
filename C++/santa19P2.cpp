#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

typedef std::map<std::string, std::string> RuleBook;

int main() {
    std::ifstream file("in");
    std::string line;

    RuleBook rules;
    std::map<std::string, bool> seen;
    std::vector<std::string> tokens;

    bool finishedRules = false;
    std::string genome;

    while (getline(file, line)) {
        if (line == "") {
            finishedRules = true;
        } else {
            if (finishedRules) {
                genome = line;
            } else {
                std::stringstream iss(line);
                tokens.clear();
                copy(std::istream_iterator<std::string>(iss),
                        std::istream_iterator<std::string>(),
                        std::back_inserter(tokens));

                rules[tokens[2]] = tokens[0];
            }
        }
    }

    std::cout << "Goal is " << genome << std::endl;
    for (auto e : rules) {
        std::cout << e.first << " => " << e.second << std::endl;

    }
}
