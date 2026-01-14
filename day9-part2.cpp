#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

// 定義 PointPair 結構來儲存一條線的兩個端點索引
struct PointPair {
    int p1_idx; // index in redBlocks
    int p2_idx; // index in redBlocks
};

// 輔助函式：檢查兩點之間是否存在於 linePairs 中
bool hasConnection(const std::vector<PointPair>& lines, int idx1, int idx2) {
    for (const auto& line : lines) {
        if ((line.p1_idx == idx1 && line.p2_idx == idx2) ||
            (line.p1_idx == idx2 && line.p2_idx == idx1)) {
            return true;
        }
    }
    return false;
}

// 輔助函式：取得兩點索引並回傳 PointPair
PointPair makePair(int idx1, int idx2) {
    return {idx1, idx2};
}

int main() {
    // Read inputs and form red blocks
    std::vector<std::pair<int, int>> redBlocks;
    std::ifstream inputFile("input-day9");
    if (!inputFile) {
        std::cerr << "Error: Could not open input-day9" << std::endl;
        return 1;
    }

    std::pair<int, int> block;
    char junk;
    while (inputFile >> block.first >> junk >> block.second) {
        redBlocks.push_back(block);
    }

    // 1. 建構 linePairs: 建構所有直線的 pairs
    std::vector<PointPair> linePairs;
    for (size_t i = 0; i < redBlocks.size(); ++i) {
        for (size_t j = i + 1; j < redBlocks.size(); ++j) {
            // if (redBlock 和 anotherRedBlock 的 x 或 y 座標是一樣的)
            if (redBlocks[i].first == redBlocks[j].first || 
                redBlocks[i].second == redBlocks[j].second) {
                // 把 red, another 放入 linePairs
                linePairs.push_back({(int)i, (int)j});
            }
        }
    }

    // 2. 建構 possibleRect: 所有可以圈起來形成封閉 rectangle 的直線集合
    // 這裡我們實作邏輯：枚舉兩個點作為矩形的「對角線」，並檢查構成矩形的四邊是否都在 linePairs 裡
    std::vector<std::vector<PointPair>> possibleRect;
    
    for (size_t i = 0; i < redBlocks.size(); ++i) {
        for (size_t j = i + 1; j < redBlocks.size(); ++j) {
            auto p1 = redBlocks[i];
            auto p3 = redBlocks[j];

            // 如果兩點不在同一行也不在同一列（構成對角線）
            if (p1.first != p3.first && p1.second != p3.second) {
                
                // 找出推斷的另外兩個角點 (Corner 2 and Corner 4)
                // c2: (p3.x, p1.y), c4: (p1.x, p3.y)
                int p2_idx = -1;
                int p4_idx = -1;

                // 在 redBlocks 中尋找這兩個推斷點是否存在
                for (size_t k = 0; k < redBlocks.size(); ++k) {
                    if (redBlocks[k].first == p3.first && redBlocks[k].second == p1.second) p2_idx = k;
                    if (redBlocks[k].first == p1.first && redBlocks[k].second == p3.second) p4_idx = k;
                }

                // 如果四個點都存在，且四條邊都在 linePairs 裡面
                if (p2_idx != -1 && p4_idx != -1) {
                    bool line1 = hasConnection(linePairs, (int)i, p2_idx); // p1 -> p2
                    bool line2 = hasConnection(linePairs, p2_idx, (int)j); // p2 -> p3
                    bool line3 = hasConnection(linePairs, (int)j, p4_idx); // p3 -> p4
                    bool line4 = hasConnection(linePairs, p4_idx, (int)i); // p4 -> p1

                    if (line1 && line2 && line3 && line4) {
                        // 建立 tempRect
                        std::vector<PointPair> tempRect;
                        tempRect.push_back(makePair((int)i, p2_idx));
                        tempRect.push_back(makePair(p2_idx, (int)j));
                        tempRect.push_back(makePair((int)j, p4_idx));
                        tempRect.push_back(makePair(p4_idx, (int)i));
                        
                        possibleRect.push_back(tempRect);
                    }
                }
            }
        }
    }

    // 3. 計算 result
    long long result = 0;
    // 計算所有 possibleRect 的 rectangle 面積，並取最大的放進 result
    for (const auto& rect : possibleRect) {
        // 取出一條邊來計算長寬 (rect[0] 是 p1-p2, rect[1] 是 p2-p3)
        // 假設 rect 裡面的順序如上建立
        auto p1 = redBlocks[rect[0].p1_idx];
        auto p2 = redBlocks[rect[0].p2_idx]; // p1, p2 形成一邊
        auto p3 = redBlocks[rect[1].p2_idx]; // p2, p3 形成鄰邊

        long long width = std::abs(p1.first - p2.first) + std::abs(p1.second - p2.second) + 1;
        long long height = std::abs(p2.first - p3.first) + std::abs(p2.second - p3.second) + 1;
        
        // 修正：上述計算因為有一邊座標差是0，所以加法沒問題，但標準矩形長寬應為 (dx+1) * (dy+1)
        // 這裡因為 p1-p2 只有 x 差或 y 差，另一個為 0，所以上面的 abs + abs 是正確的邊長計算
        
        // 但為了符合原始 skeleton 的計算邏輯 (dx+1)*(dy+1) 針對對角線：
        // 我們直接拿矩形的對角點 (p1 和 p3) 來算面積
        long long area = (long long)(std::abs(p1.first - p3.first) + 1) * (std::abs(p1.second - p3.second) + 1);

        if (area > result) {
            result = area;
        }
    }

    std::cout << result << std::endl;
}
