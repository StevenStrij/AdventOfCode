#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <iterator>
#include <algorithm>

std::map<std::vector<int>, bool> seen;

int getAmount(const std::vector<int>& buckets, std::vector<int> at, int amount) {
    if (amount < 0) return 0;

    sort(at.begin(), at.end());
    if (seen.find(at) != seen.end()) return 0;

    seen[at] = true;
    if (amount == 0) {
        return 1;
    }

    int sum = 0;
    for (auto i : buckets) {
        std::vector<int> t(at);
        t.push_back(i);
        sum += getAmount(buckets, t, amount - i);
    }

    return sum;
}

int main() {
    std::ifstream file("in");
    std::string line;
    std::vector<int> buckets;

    while (getline(file, line)) {
        buckets.push_back(stoi(line));
    }

    copy(buckets.begin(), buckets.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::vector<int> t;
    std::cout << getAmount(buckets, t, 150) << std::endl;;
}
