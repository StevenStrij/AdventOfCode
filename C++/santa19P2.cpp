#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

typedef std::map<std::string, std::vector<std::string> > RuleBook;

class State {
    public:
        unsigned int steps = 0;
        std::string curr;

        State(std::string c, unsigned int s) : steps{s}, curr{c} {}
};

void search(RuleBook& rules, std::string& end) {
    std::vector<State> states;
    std::map<std::string, bool> seen;

    State currState("", 0);
    states.push_back(State("e", 0));

    while (states.size()) {
        currState = states.back();
        states.pop_back();

        if (currState.curr == end) {
            break;
        }

        for (auto rule : rules) {
            for (auto part = currState.curr.find(rule.first); part != std::string::npos;
                      part = currState.curr.find(rule.first, part + 1)) {
                
                for (auto app : rule.second) {
                    std::string t = currState.curr;
                    t.replace(part, rule.first.length(), app, 0, app.length());

                    if (currState.curr.length() <= end.length() && seen.find(t) == seen.end()) {
                        seen[t] = true;
                        states.push_back(State(t, currState.steps + 1));
                    }
                }
            }
        }
    }
    std::cout << "Found after " << currState.steps << " steps" << std::endl;
}

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

                rules[tokens[0]].push_back(tokens[2]);
            }
        }
    }

    search(rules, genome);
}
