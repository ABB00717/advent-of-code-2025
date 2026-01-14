#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <map>

// 清理字串：將非數字的符號換成空格
std::string cleanString(std::string s) {
    for (char &c : s) {
        if (c == '[' || c == ']' || c == '(' || c == ')' || c == '{' || c == '}' || c == ',') {
            c = ' ';
        }
    }
    return s;
}

// 解析一行輸入
bool parseLine(const std::string& line, unsigned int& target, std::vector<unsigned int>& buttons) {
    buttons.clear();
    target = 0;

    size_t patternStart = line.find('[');
    size_t patternEnd = line.find(']');
    
    // 1. 解析 Target Pattern
    if (patternStart != std::string::npos && patternEnd != std::string::npos) {
        std::string pattern = line.substr(patternStart + 1, patternEnd - patternStart - 1);
        for (size_t i = 0; i < pattern.length(); ++i) {
            if (pattern[i] == '#') {
                target |= (1 << i);
            }
        }
    } else {
        return false;
    }

    // 2. 解析 Buttons (...) 
    // 我們忽略 {cost}，直接讀取所有的 (...)
    // 技巧：我們只掃描 ']' 之後的所有內容，尋找 '(' 和 ')'
    
    size_t scanPos = patternEnd + 1;
    while (true) {
        size_t openP = line.find('(', scanPos);
        if (openP == std::string::npos) break; // 找不到下一個 (
        
        size_t closeP = line.find(')', openP);
        if (closeP == std::string::npos) break; // 格式錯誤
        
        // 提取括號內的內容
        std::string content = line.substr(openP + 1, closeP - openP - 1);
        
        // 解析數字並轉為 Mask
        unsigned int mask = 0;
        std::stringstream ss(cleanString(content));
        int idx;
        while (ss >> idx) {
            mask |= (1 << idx);
        }
        
        buttons.push_back({mask});
        
        // 移動搜尋指標
        scanPos = closeP + 1;
    }

    return true;
}

// 核心演算法：BFS (無權重最短路徑)
int solveBFS(const std::vector<unsigned int>& buttons, unsigned int target) {
    std::queue<std::pair<unsigned int, int>> q; // {current_state, steps}
    std::map<unsigned int, bool> visited;       // 記錄已訪問狀態

    // 初始狀態
    q.push({0, 0});
    visited[0] = true;

    while (!q.empty()) {
        unsigned int current = q.front().first;
        int steps = q.front().second;
        q.pop();

        if (current == target) {
            return steps;
        }

        // 嘗試按下每一個按鈕
        for (const auto& btn : buttons) {
            unsigned int next = current ^ btn;

            if (!visited[next]) {
                visited[next] = true;
                q.push({next, steps + 1});
            }
        }
    }

    return -1; // 無解
}

int main() {
    std::ifstream inputFile("input-day10");
    std::string line;
    int total_steps = 0;
    int lineNum = 1;

    if (!inputFile.is_open()) {
        std::cerr << "Error: Cannot open file 'temp'" << std::endl;
        return 1;
    }

    while (std::getline(inputFile, line)) {
        if (line.empty()) continue;

        unsigned int target;
        std::vector<unsigned int> buttons;

        if (parseLine(line, target, buttons)) {
            int steps = solveBFS(buttons, target);
            if (steps != -1) {
                std::cout << "Line " << lineNum << ": " << steps << " steps" << std::endl;
                total_steps += steps;
            } else {
                std::cerr << "Line " << lineNum << ": Unsolvable" << std::endl;
            }
        }
        lineNum++;
    }

    std::cout << "Total Steps: " << total_steps << std::endl;
    return 0;
}
