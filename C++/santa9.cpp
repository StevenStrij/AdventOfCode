#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <map>
#include <queue>

typedef std::pair<std::string, int> Road;
typedef std::map<std::string, std::vector<Road> > Roads;

class State {
    public:
        std::map<std::string, bool> seen;
        std::string curr;
        int currDist;
        std::vector<std::string> path;

        State(std::string c, int cD) : curr{c}, currDist{cD} {}
        State(const State& s) {
            curr = s.curr;
            currDist = s.currDist;
            seen = s.seen;
            path = s.path;
        }
};

int findMin(const std::string& start, Roads& roads) {

    auto comp = [] (const State& a, const State& b) { return a.currDist < b.currDist; };
    typedef std::priority_queue<State, std::vector<State>, decltype(comp) > prioQ;
    prioQ q(comp);

    q.push(State{start, 0});

    State currState{start, 0};;
    while (q.size()) {
        currState = q.top();
        q.pop();

        bool finished = true;
        for (auto r : roads[currState.curr]) {
            if (currState.seen.find(r.first) == currState.seen.end()) {
                State t{currState};
                
                t.currDist += r.second;
                t.curr = r.first;
                t.path.push_back(r.first);
                t.seen[currState.curr] = true;

                q.push(t);
                
                finished = false;
            }
        }

        if (finished) {
            break;
        }

    }

    std::cout << "Min was " << currState.currDist << std::endl;
    std::cout << "Path was: " << std::endl;
    std::copy(currState.path.begin(), currState.path.end(), std::ostream_iterator<std::string>(std::cout, ", "));
    std::cout << std::endl;

    return currState.currDist;
}

int main() {
    std::ifstream file("in");
    std::string line;
    std::vector<std::string> elements;
    Roads roads;

    while (getline(file, line)) {
        std::istringstream iss(line);
        elements.clear();
        copy(std::istream_iterator<std::string>(iss),
             std::istream_iterator<std::string>(),
             std::back_inserter(elements));

        roads[elements[0]].push_back(std::make_pair(elements[2], stoi(elements[4])));
        roads[elements[2]].push_back(std::make_pair(elements[0], stoi(elements[4])));
    }

    for (auto e : roads) {
        std::cout << "City " << e.first << " has connections:" << std::endl;
        for (auto r : e.second) {
            std::cout << "\t" << r.first << " = " << r.second << std::endl;
        }
    }
    
    for (auto e : roads) {
        std::cout << "Min traversal for start of " << e.first << " was " << findMin(e.first, roads) << std::endl;
    
    }
}
