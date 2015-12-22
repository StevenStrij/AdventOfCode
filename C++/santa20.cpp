#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <map>

bool analyse = false;

unsigned long getNum(const unsigned long& num) {

    int sum = 0;
    int atNum = 1;
    int lim = (int)std::sqrt(num);

    while (atNum <= lim) {
        if (atNum % num == 0) {
            sum += atNum * 10 * (num / atNum);
        }
        ++atNum;
    }
    sum += num * 10;
    return sum;
}

int main(int argc, char* argv[]) {
    if (argc < 2) return -1;

    unsigned long in = stoi(std::string(argv[1]));

    unsigned long atNum = 0;
    unsigned long sum = 1;

    while (sum < in && atNum < 10) {
        ++atNum;
        sum = getNum(atNum);

        std::cout << atNum << " " << sum << std::endl;
    }
    std::cout << atNum << std::endl;
}
