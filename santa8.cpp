#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <fstream>

unsigned int countSubString(const std::string& string, const std::string& subStr) {
    if (string.length() == 0) return 0;

    unsigned int count = 0;
    for (auto offset = string.find(subStr); offset != std::string::npos; 
        offset = string.find(subStr, offset + subStr.length())) {
        
        ++count;
    }

    return count;
}

int main() {
    std::string line;
    std::ifstream file("in");

    unsigned int printChar = 0;
    unsigned int codeChar = 0;
    while (getline(file, line)) {
        unsigned int count = line.length() - 2;
        
        std::stringstream iss(line);

        count -= countSubString(line, "\\\\");
        count -= countSubString(line, "\\\"");
        count -= countSubString(line, "\\x")*3;

        printChar += count;
        codeChar += line.length();
    }

    file.close();

    std::cout << codeChar - printChar << std::endl;
}
