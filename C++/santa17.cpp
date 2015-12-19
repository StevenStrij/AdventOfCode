#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <iterator>
#include <algorithm>

int main() {
    std::ifstream file("in");
    std::string line;
    std::vector<int> buckets;
    int goal = 150;

    while (getline(file, line)) {
        buckets.push_back(stoi(line));
    }

    copy(buckets.begin(), buckets.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    int found = 0;
    int min = buckets.size();
    int numBuckets = 0;
    for (unsigned int i = 0; i < (1 << buckets.size()); ++i) {
        int sum = 0;
        int p = 0;
        int q = i;
        numBuckets = 0;
        while (q) {
            if (q % 2) {
                sum += buckets[p];
                ++numBuckets;
            }
            q >>= 1;
            ++p;
        }

        if (sum == goal) {
            if (numBuckets < min) {
                std::cout << "New min is " << numBuckets << std::endl;
                min = numBuckets;
                found = 0;
            }
            if (numBuckets == min) {
                ++found;
            }
        }
    }

    std::cout << found << std::endl;
}
