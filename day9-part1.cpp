/*
* Example Inputs:
* // input-day9
* 7,1
* 11,1
* 11,7
* 9,7
* 9,5
* 2,5
* 2,3
* 7,3
* EOF
*
* This program finds the largest rectangle that uses 2 points for two of its opposite corners.
*/
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>
int main() {
    // Read inputs and form points
    std::vector<std::pair<int, int>> points;
    std::ifstream inputFile("input-day9");
    std::pair<int, int> point;
    char junk;
    while (inputFile >> point.first >> junk >> point.second) {
        points.push_back(point);
    }

    long long result = 0;
    for (int i = 0; i < points.size(); i++) {
        for (int j = i+1; j < points.size(); j++) {
            // abs(point1x - point2x) * abs(point1y - point2y)
            auto point1 = points[i];
            auto point2 = points[j];
            long long t = (long long)(std::abs(point1.first - point2.first) + 1) * (std::abs(point1.second - point2.second) + 1);
            result = t > result ? t : result;
        }
    }

    std::cout << result << std::endl;
}
