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
    std::vector<std::vector<int>> numbers;
    std::vector<char> operators;
    while (std::getline(inputFile, line)) {
        int number;
        char oper;
        std::vector<int> line_numbers;

        // Read numbers in line
        if (std::isdigit(line[0])) {
            std::stringstream ss(line);
            while (ss >> number) {
                line_numbers.push_back(number);
            }

            numbers.push_back(line_numbers);
        } else {
            // Read operators in line
            std::stringstream ss(line);
            while (ss >> oper) {
                operators.push_back(oper);
            }
        }
    }

    std::cout << "pass\n";

    int n = operators.size();
    long long result = 0;
    // Performing operations;
    for (int i = 0; i < n; i++) {
        long long temp = numbers[0][i];
        for (int row = 1; row < numbers.size(); row++) {
            switch (operators[i]) {
                case '+':
                    temp += numbers[row][i];
                    break;
                case '*':
                    temp *= numbers[row][i];
                    break;
                default:
                    std::cout << "Unknows operations!\n";
                    exit(-1);
            }
        }

        result += temp;
    }

    std::cout << result << std::endl;
}
