#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int main() {
    std::vector<std::string> fields;
    int result = 0;

    // Read inputs into inputFile
    std::ifstream inputFile("input-day7");
    std::string line;
    while (std::getline(inputFile, line)) {
        fields.push_back(line);
    }

    for (char &ch : fields[0]) {
        if (ch == 'S') {
            ch = '|';
        }
    }

    for (int row = 1; row < fields.size(); row++) {
        for (int col = 0; col < fields[0].size(); col++) {
            if (fields[row - 1][col] == '|') {
                if (fields[row][col] != '^') {
                    fields[row][col] = '|';
                } else {
                    result++;
                    if (col != 0 && fields[row][col-1] != '^')
                        fields[row][col-1] = '|';
                    if (col != fields[0].size()-1 && fields[row][col+1] != '^')
                        fields[row][col+1] = '|';
                }
            }
        }
    }

    /*
    for (each row start from row2) {
        if (up block is '|') {
            if (this block isn't '^') {
                turn this block to '|' as well
            } else {
                turn left and right block to '|' if that block is '.'
                result++;
            }
        }
    }
    */

    std::cout << result << std::endl;
}
