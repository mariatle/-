#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

std::vector<int> p, sz;

int get(int v) {
    if (p[v] == v) return v;
    return p[v] = get(p[v]);
}

bool un(int a, int b) {
    a = get(a);
    b = get(b);
    if (a == b) return false;
    if (sz[a] < sz[b]) std::swap(a, b);
    p[b] = a;
    sz[a] += sz[b];
    return true;
}

double dist(std::pair<int, int> a, std::pair<int, int> b) {
    return std::sqrt((a.first - b.first) * (a.first - b.first) + 
                    (a.second - b.second) * (a.second - b.second));
}

int main()
{
    int n; std::cin >> n;
    std::vector<std::pair<int, int>> point;
    std::vector<std::pair<double, std::pair<int, int>>> ed;
    for (int i = 0; i < n; i++) {
        int a, b; std::cin >> a >> b;
        point.emplace_back(a, b);
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ed.emplace_back(dist(point[i], point[j]), std::make_pair(i, j));
        }
    }
    for (int i = 0; i < n; i++) {
        p.push_back(i);
        sz.push_back(1);
    }
    sort(ed.begin(), ed.end());
    double ans = 0;
    for (auto el : ed) {
        if (un(el.second.first, el.second.second)) {
            ans += el.first;
        }
    }
    std::cout.precision(2);
    std::cout << std::fixed << ans << std::endl;
    return 0;
}
