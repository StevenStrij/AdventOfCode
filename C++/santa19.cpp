#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

int main() {
    std::ifstream file("in");
    std::string line;

    std::map<std::string, std::vector<std::string> > rules;
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

                rules[tokens[0]].push_back(tokens[2]);
            }
        }
    }

    for (auto rule : rules) {
            for (auto part = genome.find(rule.first); part != std::string::npos;
                      part = genome.find(rule.first, part + 1)) {
                for (auto app : rule.second) {
                    std::string t = genome;
                    t.replace(part, rule.first.length(), app, 0, app.length());
                    seen[t] = true;
                }
            }
    }

    std::cout << seen.size() << std::endl;
}
