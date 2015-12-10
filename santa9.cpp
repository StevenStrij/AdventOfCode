#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <map>

class Node {
    std::string name;
    std::map<std::string, int> edges;

    Node() {}
};

class State {
    std::string curr;
    std::vector<std::string> seen;

    int currCost;

    State() { }
};

int main() {
    std::ifstream file("in");
    std::string line;
    std::vector<std::string> elements;
    std::vector<Node> nodes;

    while (getline(file, line)) {
        std::istringstream iss(line);
        elements.clear();
        copy(std::istream_iterator<std::string>(iss),
             std::istream_iterator<std::string>(),
             std::back_inserter(elements));

        if (nodes.find(elements[0]) != nodes.end()) {

        }
    }

    for (auto e = edges.begin(); e != edges.end(); ++e) {
        std::cout << e->first << std::endl;
        for (auto q = e->second.begin(); q != e->second.end(); ++q) {
            std::cout << "\t" << q->first << " = " << q->second << std::endl;
        }
    }
}
