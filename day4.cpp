#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

int paper_around(std::vector<std::string>& fields, int row, int col) {
    int result = 0;
    for (int i = row-1; i <= row+1; i++) {
        for (int j = col-1; j <= col+1; j++) {
            if (!(i == row && j == col) && i >= 0 && i < fields.size() && j >= 0 && j < fields[0].size()) {
                if (fields[i][j] == '@')
                    result++;
            }
        }
    }

    return result;
}

void print_fields(std::vector<std::string>& fields) {
    for (std::string line : fields) {
        std::cout << line << std::endl;
    }
}

int main() {
    std::vector<std::string> fields;

    std::ifstream inputFile("input");
    std::string line;
    while (inputFile >> line) {
        fields.push_back(line);
    }

    bool changed = false;
    int result = 0;
    do {
        changed = false;
        for (int i = 0; i < fields.size(); i++) {
            for (int j = 0; j < fields[0].size(); j++) {
                if (fields[i][j] == '@' && paper_around(fields, i, j) < 4) {
                    fields[i][j] = '.';
                    result++;
                    changed = true;
                }
            }
        }
    } while (changed);

    print_fields(fields);
    std::cout << result << std::endl;
}
