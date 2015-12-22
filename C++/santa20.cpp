#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

bool analyse = false;

unsigned long getNum(const unsigned long& num) {

    int sum = 0;
    unsigned long atNum = 1;
    unsigned long lim = num / 2;
    unsigned long numFactors = 0;

    while (atNum <= lim) {
        if (num % atNum == 0) {
            sum += atNum*10;
            ++numFactors;
        }

        ++atNum;
    }
    sum += num * 10;

    if (analyse) {
        std::cout << "Number: " << num << ", " <<
                     "Sum: " << sum << ", " <<
                     "NumFactors: " << numFactors << std::endl;
                 
    }
    return sum;
}

int main(int argc, char* argv[]) {
    if (argc < 2) return -1;

    unsigned long in = stoi(std::string(argv[1]));

    unsigned long atNum = 0;
    unsigned long sum = 1;

    while (sum < in) {
        ++atNum;
        sum = getNum(atNum);

        if (atNum % 1000 == 0) {
            std::cout << atNum << " " << sum << std::endl;
        }
    }
}
