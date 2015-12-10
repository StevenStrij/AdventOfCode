#include <iostream>
#include <fstream>
#include <map>
#include <regex>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <stdio.h>

static const unsigned int NOT = 0;
static const unsigned int AND = 1;
static const unsigned int OR = 2;
static const unsigned int RSHIFT = 3;
static const unsigned int LSHIFT = 4;
static const unsigned int LOAD = 5;

typedef std::map<std::string, std::string> Memory;
typedef std::map<std::string, uint16_t> Result;


uint16_t eval(Memory& oper, Result& resMem,std::string curr) {
    if (curr.find_first_not_of( "0123456789" ) == std::string::npos) {
        return stoi(curr);
    }

    if (resMem.find(curr) != resMem.end()) {
        return resMem[curr];
    }

    std::string toEval = oper[curr];

    std::stringstream iss(toEval);
    std::string ele;
    std::vector<std::string> elements;

    while (getline(iss, ele, ' ')) {
        elements.push_back(ele);
    }

    if (elements[0] == "~") {
        uint16_t res = eval(oper, resMem, elements[1]);
        resMem[curr] = ~res;
        
        return ~res;
    } else if (elements.size() == 1) {
        return eval(oper, resMem, elements[0]);
    } else {
        uint16_t res1 = eval(oper, resMem, elements[0]);
        uint16_t res2 = eval(oper, resMem, elements[2]);

        if (elements[1] == "|") {
            resMem[curr] = res1 | res2;
            return res1 | res2;
        } else if (elements[1] == "&") {
            resMem[curr] = res1 & res2;
            return res1 & res2;
        } else if (elements[1] == ">>") {
            resMem[curr] = res1 >> res2;
            return res1 >> res2;
        } else if (elements[1] == "<<") {
            resMem[curr] = res1 << res2;
            return res1 << res2;
        }
    }

    return 0;
}

int main() {
    std::ifstream file("in");
    std::string line;
    std::vector<std::string> tokens;

    Memory memory;
    Result res;

    while (getline(file, line)) {
        std::stringstream iss(line);
        std::string token;
        tokens.clear();

        while (getline(iss, token, '=')) {
            token.erase(token.begin(), std::find_if(token.begin(), token.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
            token.erase(std::find_if(token.rbegin(), token.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), token.end());

            tokens.push_back(token);

        }
        memory[tokens[0]] = tokens[1];
    }

    std::cout << "Wire A has value " << eval(memory, res, "a");
}
