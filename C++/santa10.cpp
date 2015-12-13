#include <iostream>
#include <fstream>
#include <sstream>

int main() {

    std::string str = "3113322113";
    std::string next{};
    char curr = str[0];

    int count = 1;
    int numIter = 50;

    for (int i = 0; i < numIter; ++i) {
        
        count = 0;
        curr = str[0];
        for (auto c : str) {
            if (c == curr) {
                ++count;
            } else {
                std::stringstream ss;
                std::string temp;
                ss << count;
                ss << curr;
                ss >> temp;
                next += temp;
                count = 1;
            }

            curr = c;
        }
        std::stringstream ss;
        std::string temp;
        ss << count;
        ss << curr;
        ss >> temp;
        next += temp;

        str = next;
        next = "";
    }


    std::cout << "Final len was " << str.length() << std::endl;


    return 0;
}
