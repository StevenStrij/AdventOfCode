#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <map>

typedef std::pair<std::string, int> Edge;

int main() {
    std::ifstream file("in");
    std::string line;
    std::vector<std::string> elements;
    std::map<std::string, std::vector<std::pair<std::string, int> > > edges;

    while (getline(file, line)) {
        std::istringstream iss(line);
        copy(std::istream_iterator<std::string>(iss),
             std::istream_iterator<std::string>(),
             std::back_inserter(elements));

        Edge e = std::make_pair(elements[2], stoi(elements[4]));
        edges[elements[0]].push_back(e);
    }

    for (auto e = edges.begin(); e != edges.end(); ++e) {
        std::cout << e->first << std::endl;
        for (auto q = e->second.begin(); q != e->second.end(); ++q) {
            std::cout << "\t" << q->first << " = " << q->second << std::endl;
        }
    }
}
