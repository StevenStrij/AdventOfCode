#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <regex>

class Ingrediant {
    public:
        int cap, dur, flav, tex, cal;
        std::string name;

        Ingrediant(std::string n, int c, int d, int f, int t, int cl) : cap{c}, dur{d}, flav{f}, tex{t}, cal{cl}, name{n} {}

        std::vector<int> calculateScore(int n) {
            std::vector<int> vec;
            vec.push_back(cap * n);
            vec.push_back(dur * n);
            vec.push_back(flav * n);
            vec.push_back(tex * n);
            vec.push_back(cal * n);

            return vec;
        }

};

int getMax(std::vector<Ingrediant>& ingrediants,
           std::vector<int> used, int curPos, int res) {

    int best = 0;
    bool debug = false;
    for (int i = res; i >= 1; --i) {
        if (curPos == (int)ingrediants.size() - 1) {
            std::vector<int> sum{0, 0, 0, 0, 0};
            int score = 0;
            used.push_back(res);


            for (int j = 0; j < (int)ingrediants.size(); ++j) {
                std::vector<int> tmp = ingrediants[j].calculateScore(used[j]);
                sum[0] += tmp[0];
                sum[1] += tmp[1];
                sum[2] += tmp[2];
                sum[3] += tmp[3];
                sum[4] += tmp[4];
            }
            for (int j = 0; j < (int)ingrediants.size(); ++j) {
                sum[0] = std::max(0, sum[0]);
                sum[1] = std::max(0, sum[1]);
                sum[2] = std::max(0, sum[2]);
                sum[3] = std::max(0, sum[3]);
                sum[4] = std::max(0, sum[4]);
            }

            if (sum[4] != 500) return 0;

            score = sum[0] * sum[1] * sum[2] * sum[3];

            if (debug) {
                std::cout << "Inspecting ingr: ";
                copy(used.begin(), used.end(), std::ostream_iterator<int>(std::cout, " "));
                std::cout << std::endl << "Sums were: ";
                copy(sum.begin(), sum.end(), std::ostream_iterator<int>(std::cout, " "));
                std::cout << std::endl << "Returning " << score << std::endl;


            }

            return score;
        } else {
            std::vector<int> tmp(used);
            tmp.push_back(i);
            int score = getMax(ingrediants, tmp, curPos + 1, res - i);

            if (score > best) {
                best = score;
            }
        }
    }

    return best;
}

int main() {
    std::ifstream file("in");
    std::string line;

    std::regex exp("(.*): capacity (-?\\d+), durability (-?\\d+), flavor (-?\\d+), texture (-?\\d+), calories (-?\\d+)");
    std::smatch match;

    std::vector<Ingrediant> ingrediants;

    while (getline(file, line)) {
        while (std::regex_search(line, match, exp)) {

            ingrediants.push_back(Ingrediant{match[1],
                    stoi(match[2]),
                    stoi(match[3]),
                    stoi(match[4]),
                    stoi(match[5]),
                    stoi(match[6])});

            line = match.suffix().str();
        }
    }

    std::vector<int> tmp;
    std::cout << getMax(ingrediants, tmp, 0, 100) << std::endl;
    return 0;
}



















