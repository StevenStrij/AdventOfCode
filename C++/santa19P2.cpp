#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

typedef std::map<std::string, std::string> RuleBook;

class State {
    public:
        unsigned int steps = 0;
        std::string curr;

        State(std::string c, unsigned int s) { curr = c; steps = s; }
};

void search(RuleBook& rules, std::string end) {
    std::vector<std::string> states;
    std::map<std::string, bool> seen;

    std::string currState = "";
    states.push_back(end);

    unsigned int q = 0;
    unsigned int w = end.length();
    while (states.size()) {
        currState = states.back();
        states.pop_back();

        if (currState == "e") {
            break;
        }

        ++q;

        //if (q != currState.steps) {
        //    std::cout << "Max was: " << max << std::endl;
        //    for (auto i = states.rbegin(); i != states.rbegin() + 5; ++i) {
        //        std::cout << "\t" << i->curr.length() << std::endl;
        //    }
        //    std::cout << std::endl;
        //    max = 0;
        //}

        for (auto rule : rules) {
            std::string t = "";
            for (auto part = currState.find(rule.first); part != std::string::npos;
                    part = currState.find(rule.first, part + 1)) {

                unsigned int min1 = end.length();
                std::for_each(states.begin(), states.end(),
                                [&min1] (const std::string& s) {
                                    if (s.length() < min1) {
                                        min1 = s.length();
                                    }
                            });
                
                t = currState;
                t.replace(part, rule.first.length(), rule.second, 0, rule.second.length());

                if (seen.find(t) != seen.end()) continue;

                seen[t] = true;
                states.push_back(t);

                unsigned int min2 = end.length();
                std::for_each(states.begin(), states.end(),
                                [&min2] (const std::string& s) {
                                    if (s.length() < min2) {
                                        min2 = s.length();
                                    }
                            });
                

                if (min1 != min2 && min2 != t.length()) {
                    std::cout << "Before " << currState << std::endl;
                    std::cout << "After  " << t << std::endl;
                    std::cout << "wth" << std::endl;
                    return;
                }
            }
        }
    }
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

                rules[tokens[2]] = tokens[0];
            }
        }
    }

    search(rules, genome);
}
