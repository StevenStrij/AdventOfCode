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
        
        if (subStr == "\\x" || subStr == "\\\"") {
            int t = 0;
            int p = 1;
            while (string[offset - p] == '\\') {
                ++t;
                ++p;
            }
            if (t % 2 == 1) {
                continue;
            }
        }

        ++count;
    }

    std::cout << "Found " << count << " of " << subStr << std::endl;
    return count;
}

int main() {
    std::string line;
    std::ifstream file("in");

    unsigned int printChar = 0;
    unsigned int codeChar = 0;
    while (getline(file, line)) {
        bool inEscape = false;
        unsigned int count = 0;
        for (auto ch = line.begin(); ch != line.end(); ++ch) {
            if (*ch == '\"') {
                if (inEscape) {
                    count += 2;
                    inEscape = false;
                } else {
                    count += 3;
                }
            } else if (*ch == '\\') {
                inEscape = !inEscape;
                count += 2;
            } else if (*ch == 'x') {
                if (inEscape) {
                    inEscape = false;
                }
                ++count;
            } else {
                ++count;
            }
        }
        std::cout << "To print out is " << count << " for " << line << std::endl;
        printChar += line.length();
        codeChar += count;
    }

    file.close();

    std::cout << codeChar - printChar << std::endl;
}
