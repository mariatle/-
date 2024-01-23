#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> g;
std::vector<int> color;

std::pair<int, int> dfs(int v, int c) {
    color[v] = c;
    std::pair<int, int> sz = {1, 0};
    for (auto to : g[v]) {
        if (color[to] != -1) {
            if (c == color[to]) {
                return {-1, -1};
            }
        } else {
            std::pair<int, int> add = dfs(to, c^1);
            if (add.first == -1) {
                return add;
            }
            sz.first += add.second;
            sz.second += add.first;
        }
    }
    return sz;
}


int main()
{
    int n; std::cin >> n;
    g.resize(n);
    color.resize(n, -1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c; std::cin >> c;
            if (c == '+') {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }
    int cnt = 0;
    std::vector<std::pair<int, int>> comp;
    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            comp.push_back(dfs(i, cnt));
            if (comp.back().second == -1) {
                std::cout << "No solution\n";
                return 0;
            }
            cnt+=2;
        } 
    }
    int s = comp.size();
    int best_dif = n + 1;
    std::vector<int> best;
    for (int mask = 0; mask < (1 << s); mask++) {
        int fi = 0, se = 0;
        for (int i = 0; i < s; i++) {
            if (mask & (1 << i)) {
                fi += comp[i].second;
                se += comp[i].first;
            } else {
                fi += comp[i].first;
                se += comp[i].second;
            }
        }
        if (fi > se) continue;
        int dif = se - fi;
        if (dif <= best_dif) {
            std::vector<int> fi_comp;
            for (int i = 0; i < n; i++) {
                int ind = color[i] >> 1;
                if (((mask & (1 << ind)) >> ind) == (color[i] & 1)) {
                    fi_comp.push_back(i);
                }
            }
            if (dif < best_dif) {
                best_dif = dif;
                best = fi_comp;
            } else {
                int ind = 0;
                while (ind < best.size() && ind < fi_comp.size()) {
                    if (best[ind] != fi_comp[ind]) break;
                    ind++;
                }
                if (ind == best.size()) continue;
                if (ind == fi_comp.size() || best[ind] > fi_comp[ind]) {
                    best = fi_comp;
                } 
            }
        }
    }
    for (auto v : best) {
        std::cout << v + 1 << " ";
    }
    std::cout << "\n";
    return 0;
}
