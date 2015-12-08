#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

int main() {
    fstream in("in");
    string line;

    int validCount = 0;

    bool duoV = false;
    bool triV = false;

    map<string, int> pairs;

    while (getline(in, line)) {

        duoV = false;
        triV = false;
        pairs.clear();
        for (string::iterator c = line.begin(); c != line.end(); ++c) {
            if (c != line.begin()) {
                string temp{};
                temp += *(c - 1);
                temp += *c;
                if (pairs.find(temp) == pairs.end()) {
                    pairs[temp] = c  - line.begin();
                } else {
                    if (c - line.begin() - pairs[temp] > 1) {
                        duoV = true;
                    }
                }

                if (line.end() - c > 1) {
                    if (*(c - 1) == *(c + 1) && *c != *(c + 1)) {
                        triV = true;
                    }
                }
            } 
        }
        cout << duoV << " " << triV << endl;
        if (duoV && triV) ++validCount;
    }

    cout << validCount << endl;
}
