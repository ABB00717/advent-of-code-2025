#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

bool isStrictlyRepeatedTwice (std::string s) {
    int n = s.size();

    if (n % 2 != 0)
        return false;

    int half_n = n / 2;
    std::string first = s.substr(0, half_n);
    std::string second = s.substr(half_n);

    return first == second;
}

bool repeatedSubstringPattern(std::string s) {
    std::string s_merged = s + s;
    s_merged.erase(s_merged.begin());
    s_merged.pop_back();

    return s_merged.find(s) != std::string::npos;
}

int main() {
    std::ifstream file("input");
    
    long long num1, num2;
    char junk;
    
    long long result = 0;
    while (file >> num1) {
        file >> junk;
        file >> num2;

        for (long long i = num1; i <= num2; i++) {
            if (repeatedSubstringPattern(std::to_string(i))) {
                long long t = result;
                t += i;

                std::cout << i << std::endl;
                if (t < result) {
                    std::cout << t << std::endl;
                    result = i;
                } else {
                    result = t;
                }
            }
        }

        if (file.peek() == ',')
            file >> junk;
    }

    std::cout << result << std::endl;
}
