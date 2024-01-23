#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> g;
vector<int> comp;
vector<int> sum_v, sum_e, min_v;

void dfs(int v, int c) {
    comp[v] = c;
    sum_v[c]++;
    sum_e[c] += g[v].size();
    for (auto to : g[v]) {
        if (comp[to] == -1) {
            dfs(to, c);
        }
    }
}

int main() {
    int n, m; cin >> n >> m;
    g.resize(n);
    comp.resize(n, -1);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int c = 0;
    for (int i = 0; i < n; i++) {
        if (comp[i] == -1) {
            min_v.push_back(i);
            sum_v.push_back(0);
            sum_e.push_back(0);
            dfs(i, c);
            c++;
        }
    }   
    int best = 0;
    for (int i = 0; i < c; i++) {
        if (sum_v[best] < sum_v[i]) {
            best = i;
        } else if (sum_v[best] == sum_v[i]) {
            if (sum_e[best] < sum_e[i]) {
                best = i;
            } else if (sum_e[best] == sum_e[i]) {
                if (min_v[best] > min_v[i]) {
                    best = i;
                }
            }
        }
    }
    cout << "graph {\n";
    for (int i = 0; i < n; i++) {
        if (comp[i] == best) {
            cout << i << " [color=red];\n";
        } else {
            cout << i << ";\n";
        }
    }
    for (int i = 0; i < n; i++) {
        for (auto to : g[i]) {
            if (to >= i) {
                cout << i << "--" << to;
                if (comp[i] == best) {
                    cout << " [color=red];\n";
                } else {
                    cout << ";\n";
                }
            }
        }
    }
    cout << "}\n";
    return 0;
}
