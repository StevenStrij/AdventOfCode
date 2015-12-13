#include <iostream>
#include <fstream>
#include <map>


bool solvesRule1(const std::string& str) {
    for (auto c = str.begin() + 1; c != str.end() - 1; ++c) {
        if (*c - *(c - 1) == 1 && *(c + 1) - *c == 1) {
            return true;
        }
    }

    return false;
}

bool solvesRule2(const std::string& str) {
    for (auto c : str) {
        if (c == 'i' || c == 'o' || c == 'l') {
            return false;
        }
    }
    
    return true;
}

bool solvesRule3(const std::string& str) {

    auto firstPos = str.end();
    bool firstFound = false;
    for (auto c = str.begin() + 1; c != str.end(); ++c) {
        if (*c == *(c-1) && c - firstPos != 1) {
            if (firstFound) {
                return true;
            }
            firstFound = true;
            firstPos = c;
        }
    }

    return false;
}

void next(std::string& str) {

    std::map<char, char> alpha;
    alpha['a'] = 'b';
    alpha['b'] = 'c';
    alpha['c'] = 'd';
    alpha['d'] = 'e';
    alpha['e'] = 'f';
    alpha['f'] = 'g';
    alpha['g'] = 'h';
    alpha['h'] = 'i';
    alpha['i'] = 'j';
    alpha['j'] = 'k';
    alpha['k'] = 'l';
    alpha['l'] = 'm';
    alpha['m'] = 'n';
    alpha['n'] = 'o';
    alpha['o'] = 'p';
    alpha['p'] = 'q';
    alpha['q'] = 'r';
    alpha['r'] = 's';
    alpha['s'] = 't';
    alpha['t'] = 'u';
    alpha['u'] = 'v';
    alpha['v'] = 'w';
    alpha['w'] = 'x';
    alpha['x'] = 'y';
    alpha['y'] = 'z';
    alpha['z'] = 'a';

    for (auto c = str.rbegin(); c != str.rend(); ++c) {
        *c = alpha[*c];
        if (*c != 'a') {
            break;
        }
    }
}

int main() {

    std::string curr = "hxbxxyzz";
    next(curr);

    std::cout << "Rule 1 " << solvesRule1("ghjaabcc") << std::endl;
    std::cout << "Rule 2 " << solvesRule2("ghjaabcc") << std::endl;
    std::cout << "Rule 3 " << solvesRule3("ghjaabcc") << std::endl;

    while (!(solvesRule1(curr) && solvesRule2(curr) && solvesRule3(curr))) {
        next(curr);
    }
    
    std::cout << curr << std::endl;
    return 0;
}
