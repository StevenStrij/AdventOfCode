#include <iostream>
#include <fstream>
#include <map>
#include <regex>

int main() {
    std::smatch matches;
    std::regex exp("((NOT \\w+)|(\\w+ )+)-> (\\w+)");
    std::string command;
    std::smatch match;
    std::map<std::string, int> registers;

    std::string applyTo;

    std::fstream file("in");

    while (getline(file, command)) {
        while (std::regex_search(command, match, exp)) {
            for (auto comm = match.begin(); comm != match.end(); ++comm) {
                std::cout << *comm << "-";
            }
            std::cout << std::endl;
            command = match.suffix().str();

        }
    }

    return 0;
}
