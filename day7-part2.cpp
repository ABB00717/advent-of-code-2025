/*
.......S.......
.......|.......
......|^.......
......|........
.....|^.^......
.....|.........
....|^.^.^.....
....|..........
...|^.^...^....
...|...........
..|^.^...^.^...
..|............
.|^...^.....^..
.|.............
|^.^.^.^.^...^.
|..............



.|^...^.....^.. 
.....^..^...... 
.^.^.^.^.^...^. 

int helper(index: 1, row: 13, fields: (from row+1 to end)) {
    if (fields is NULL) {
        return 1;
    }

    if (under the index the block is '^')
        // helper to left
        sum += helper(index-1, row + 1, fields(from row+2 to end)) 
        // helper to right
        sum += helper(index+1, row + 1, fields(from row+2 to end)) 
    else
        return helper(index, row + 1, fields(from row+2 to end))
}
*/

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include <span>

struct PairHash {
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1); 
    }
};

#define DPTYPE std::unordered_map<std::pair<int, int>, long long, PairHash>

// int helper(index: 1, row: 13, fields: (from row+1 to end)) {
long long helper(int index, int row, DPTYPE& dp, std::vector<std::string>& fields) {
    if (row == fields.size()-1)
        return 1;

    if (dp.count({row, index}))
        return dp[{row, index}];

    int curRow = row+1;
    long long result = 0;
    if (fields[curRow][index] == '^') {
        if (index != 0)
            result += helper(index-1, curRow, dp, fields);
        if (index != fields[0].size()-1)
            result += helper(index+1, curRow, dp, fields);
    } else {
        return helper(index, curRow, dp, fields);
    }

    return dp[{row, index}] = result;
}

int main() {
    std::vector<std::string> fields;
    long long result = 0;

    // Read inputs into inputFile
    std::ifstream inputFile("input-day7");
    std::string line;
    while (std::getline(inputFile, line)) {
        fields.push_back(line);
    }

    DPTYPE dp;
    for (int i = 0; i < fields[0].size(); i++) {
        if (fields[0][i] == 'S') {
            result = helper(i, 0, dp, fields);
        }
    }

    std::cout << result << std::endl;
}
