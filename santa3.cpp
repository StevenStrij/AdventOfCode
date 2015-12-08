#include <iostream>
#include <map>
#include <fstream>
#include <ostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    fstream file("in");
    string word;
    getline(file, word);

    vector<int> pos1{0, 0};
    vector<int> pos2{0, 0};
    map<vector<int>, bool> seen;

    bool playa = true;

    seen[pos1] = true;
    for (char p : word) {
        if (p == '^') {
            if (playa) {
                pos1[1]++; 
            } else {
                pos2[1]++; 
            }
        } else if (p == 'v') {
            if (playa) {
                pos1[1]--; 
            } else {
                pos2[1]--; 
            }
        } else if (p == '<') {
            if (playa) {
                pos1[0]--; 
            } else {
                pos2[0]--; 
            }
        } else if (p == '>') {
            if (playa) {
                pos1[0]++; 
            } else {
                pos2[0]++; 
            }
        }

        if (playa) {
            seen[pos1] = true;
        } else {
            seen[pos2] = true;
        }
        playa = !playa;
    }

    cout << seen.size() << endl;
}
