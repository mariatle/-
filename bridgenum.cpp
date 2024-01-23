#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> g;
vector<int> h;
vector<int> fup;
int cnt = 0;
vector<bool> used;

void dfs(int v, int p) {
    if (p == -1) {
        h[v] = 0;
    } else {
        h[v] = h[p] + 1;
    }
    fup[v] = h[v];
    used[v] = true;
    for (auto to : g[v]) {
        if (to == p) continue;
        if (used[to]) {
            if (h[to] < fup[v]) {
                fup[v] = h[to];
            }
        } else {
            dfs(to, v);
            if (fup[to] < fup[v]) {
                fup[v] = fup[to];
            }
        }
    }
    if (p != -1 && fup[v] == h[v]) {
        cnt++;
    } 

}

int main() {
    int n, m; cin >> n >> m;
    g.resize(n);
    fup.resize(n);
    h.resize(n);
    used.resize(n, false);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int c = 0;
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            dfs(i, -1);
        }
    }   
    cout << cnt << endl;   
    return 0;
}
