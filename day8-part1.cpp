#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define EDGE_CALC(path, x, y, z) \
    path = std::sqrt(std::pow(x, 2) +\
                    std::pow(y, 2) +\
                    std::pow(z, 2))\

typedef struct {
    int x;
    int y;
    int z;
} Point;

typedef struct {
    float weight;
    int u; // Index
    int v;
} Edge;

class DS {
public:
    std::vector<int> parent;
    std::vector<int> size;

    DS(int n) {
        parent.resize(n);
        size.resize(n, 1);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int i) {
        if (parent[i] == i) return i;
        return parent[i] = find(parent[i]);
    }

    void combine(int i, int j) {
        int root_i = find(i);
        int root_j = find(j);

        if (root_i != root_j) {
            parent[root_i] = root_j;
            size[root_j] += size[root_i];
        }
    }

    int getSize(int i) {
        return size[find(i)];
    }
};

int main() {
    std::ifstream inputFile("input-day8");
    std::string line;

    //  Store all points from inputFile
    std::vector<Point> points;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        int x, y, z;
        char junk;
        ss >> x >> junk >> y >> junk >> z;
        points.push_back({x, y, z});
    }

    //  Calculate edge basted on point1 and point2
    float edge;
    std::vector<Edge> edges;
    for (int i = 0; i < points.size(); i++) {
        for (int j = i+1; j < points.size(); j++) {
            float dx = points[i].x - points[j].x;
            float dy = points[i].y - points[j].y;
            float dz = points[i].z - points[j].z;
            EDGE_CALC(edge, dx, dy, dz);
            edges.push_back({edge, i, j});
        }
    }
    //  Sort edges (std::less) (edge, point1, point2)
    std::sort(edges.begin(), edges.end(), [](const auto& a, const auto& b){
        return a.weight < b.weight;
    });

    int limit = 1000;
    if (edges.size() < limit) limit = edges.size();

    //  Init Disjoint Set
    DS sets(points.size());
    //  Combine point1 and point2 in same disjoint set
    for (int i = 0; i < limit; i++) {
        sets.combine(edges[i].u, edges[i].v);
    }

    //  Find the 3 largest Disjoint Set
    std::vector<int> groupSize;
    std::vector<bool> filled(points.size(), false);
    // Fill the groupSize
    for (int i = 0; i < points.size(); i++) {
        int root = sets.find(i);
        if (!filled[root]) {
            filled[root] = true;
            groupSize.push_back(sets.getSize(root));
        }
    }
    std::sort(groupSize.begin(), groupSize.end(), [](const auto& a, const auto& b){
        return a > b;
    });

    long long result = groupSize[0] * groupSize[1] * groupSize[2];
    std::cout << result;
}
