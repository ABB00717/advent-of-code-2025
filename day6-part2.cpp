#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
int main() {
    std::ifstream inputFile("input-day6");

    std::string line;
    std::vector<std::string> inputLines;
    while (std::getline(inputFile, line)) {
        inputLines.push_back(line);
    }

    int lineSize = inputLines[0].size();
    int inputSize = inputLines.size();
    std::vector<long long> cur_line_numbers;
    long long result = 0;
    for (int col = lineSize-1; col >= 0; col--) {
        char dig = ' ';

        long long cur_number = 0;
        for (int row = 0; row < inputLines.size(); row++) {
            if (isdigit(inputLines[row][col])) {
                cur_number *= 10;
                cur_number += inputLines[row][col] - '0';
            }
        }

        if (cur_number != 0)
            cur_line_numbers.push_back(cur_number);

        if (inputLines[inputSize-1][col] != ' ') {
            char oper = inputLines[inputSize-1][col];
            long long temp = cur_line_numbers[0];
            switch (oper) {
                case '+':
                    for (int i = 1; i < cur_line_numbers.size(); i++) {
                        temp += cur_line_numbers[i];
                    }
                    break;
                case '*':
                    for (int i = 1; i < cur_line_numbers.size(); i++) {
                        temp *= cur_line_numbers[i];
                    }
                    break;
                default:
                    std::cout << "Unknown Operations!\n";
                    exit(-1);
            }

            result += temp;
            cur_line_numbers.clear();
            std::cout << result << std::endl;
        }
    }

    std::cout << result << std::endl;
}
