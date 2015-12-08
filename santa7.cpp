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

typedef std::map<std::string, uint16_t> Memory;

bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
            s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

void performOp(const unsigned int& op, Memory& registers,
               const std::string& term1, const std::string& term2, const std::string& apply) {

    uint16_t num1, num2;

    if (is_number(term1)) {
        num1 = stoi(term1);
    } else {
        num1 = registers[term1];
    }

    if (is_number(term2)) {
        num2 = stoi(term2);
    } else {
        num2 = registers[term2];
    }

    if (op == NOT) {
        registers[apply] = ~num1;

    } else if (op == AND) {
        registers[apply] = num1 & num2;

    } else if (op == OR) {
        registers[apply] = num1 | num2;

    } else if (op == LSHIFT) {
        registers[apply] = num1 << num2;

    } else if (op == RSHIFT) {
        registers[apply] = num1 >> num2;

    } else if (op == LOAD) {
        registers[apply] = num1;
    }
}

int main() {
    std::smatch matches;
    std::regex exp("([\\w ]+) -> (\\w+)");
    std::string command;
    std::smatch match;
    Memory registers;

    std::string applyTo;
    std::string operation;
    std::vector<std::string> tokens;

    std::fstream file("in");

    while (getline(file, command)) {
        while (std::regex_search(command, match, exp)) {
            operation = match[1];
            applyTo = match[2];
            tokens.clear();

            std::istringstream iss(operation);
            copy(std::istream_iterator<std::string>(iss),
                    std::istream_iterator<std::string>(),
                    std::back_inserter(tokens));

            if (tokens[0] == "NOT") {
                performOp(NOT, registers, tokens[1], tokens[1], applyTo);

            } else if(tokens[1] == "OR") {
                performOp(OR, registers, tokens[0], tokens[2], applyTo);

            } else if (tokens[1] == "AND") {
                performOp(AND, registers, tokens[0], tokens[2], applyTo);

            } else if (tokens[1] == "LSHIFT") {
                performOp(LSHIFT, registers, tokens[0], tokens[2], applyTo);

            } else if (tokens[1] == "RSHIFT") {
                performOp(RSHIFT, registers, tokens[0], tokens[2], applyTo);

            } else {
                performOp(LOAD, registers, tokens[0], tokens[0], applyTo);

            }


            command = match.suffix().str();
        }
    }

    std::cout << "Registers contain: " << std::endl;
    for (auto e = registers.begin(); e != registers.end(); ++e) {
        std::cout << e->first << " -> " << e->second << std::endl;
    }

    return 0;
}
