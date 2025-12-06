#include <fstream>
#include <iostream>
#include <string>
#include <cstdio>

std::string findMaxSubsequence(std::string line, int k) {
    std::string result = "";
    if (line.size() <= k)
        return line;
        
    int search_start_index = 0;

    int times = k;
    // You have to leave at least k digit for the rest
    for (int i = 0; i < times; i++) {
        char max_char = '0' - 1;
        char max_char_index = -1;
        
        // If we're searching for k digits right now,
        // then there should be at least (k-1) digit left for the 
        // rest.
        //
        // Assume that k = 3, n = 4, the search_end_index should be 2
        //
        // So the math is (4 - 3 + 1) => (n - k + 1)
        int search_end_index = line.size() - k + 1;
        for (int j = search_start_index; j < search_end_index; j++) {
            if (line[j] > max_char) {
                max_char = line[j];
                max_char_index = j;
            }

            if (max_char == '9') break;
        }

        result += max_char;
        search_start_index = max_char_index + 1;
        k--;
    }

    return result;
}

int main() {
    std::ifstream inputFile("input");

    std::string line;
    long long result = 0;
    while (inputFile >> line) {
        std::string max = findMaxSubsequence(line, 12);
        result += std::stoll(max);
    }

    std::cout << result << std::endl;
}
