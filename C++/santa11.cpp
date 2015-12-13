#include <iostream>
#include <fstream>
#include <map>

void getNextR1(std::string& str) {

    std::map<char, int> alpha;
    alpha['a'] = 0;
    alpha['b'] = 1;
    alpha['c'] = 2;
    alpha['d'] = 3;
    alpha['e'] = 4;
    alpha['f'] = 5;
    alpha['g'] = 6;
    alpha['h'] = 7;
    alpha['i'] = 8;
    alpha['j'] = 9;
    alpha['k'] = 10;
    alpha['l'] = 11;
    alpha['m'] = 12;
    alpha['n'] = 13;
    alpha['o'] = 14;
    alpha['p'] = 15;
    alpha['q'] = 16;
    alpha['r'] = 17;
    alpha['s'] = 18;
    alpha['t'] = 19;
    alpha['u'] = 20;
    alpha['v'] = 21;
    alpha['w'] = 22;
    alpha['x'] = 23;
    alpha['y'] = 24;
    alpha['z'] = 25;

    bool found = false;
    for (std::string::reverse_iterator c = str.rbegin(); c != str.rend() - 1; ++c) {
        if (alpha[*c] == alpha[*(c + 1)] + 1) {
            found = true;
        }
    }
}

int main() {

    std::string curr = "hxbxwxba"
    return 0;
}
