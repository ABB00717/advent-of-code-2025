#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
int main() {
    std::ifstream inputFile("input");

    std::vector<std::pair<long long, long long>> ranges;
    std::vector<long long> ingredients;

    std::string line;
    long long start, end;
    char junk;

    while (std::getline(inputFile, line)) {
        if (line.empty())
            break;

        std::stringstream ss(line);

        ss >> start >> junk >> end;
        ranges.emplace_back(std::pair<long long, long long>(start, end));
    }

    long long num;
    while (inputFile >> num) {
        ingredients.push_back(num);
    }

    std::sort(ranges.begin(), ranges.end());
    std::sort(ingredients.begin(), ingredients.end());

    std::vector<std::pair<long long, long long>> merged;
    merged.push_back(ranges[0]);
    // Merge the ranges if they overlape
    for (int i = 1; i < ranges.size(); i++) {
        auto &last = merged.back();
        auto &cur = ranges[i];

        if (last.second >= cur.first) {
            last.second = std::max(last.second, cur.second);
        } else {
            merged.push_back(cur);
        }
    }
    ranges = merged;

    long long result = 0;
    for (int i = 0; i < ranges.size(); i++) {
        long long start = ranges[i].first, end = ranges[i].second;
        result += (end - start) + 1;
    }

/*
    // Check if the food is spoiled
    int i_ingre = 0;
    long long result = 0;;
    for (int i_rang = 0; i_rang < ranges.size(); i_rang++) {
        long long start = ranges[i_rang].first, end = ranges[i_rang].second;
        
        // ingre valid && it's <= end
        while (i_ingre < ingredients.size() && ingredients[i_ingre] <= end) {
            if (ingredients[i_ingre] >= start)
                result++;
            i_ingre++;
        }
    }
*/

    std::cout << result << std::endl;
}
