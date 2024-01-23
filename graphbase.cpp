#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs(int v, vector<vector<int>> & g, vector<bool> & used, vector<int> & e) {
    used[v] = true;
    for (auto to : g[v]) {
        if (!used[to]) {
            dfs(to, g, used, e);
        }
    }
    e.push_back(v);
}

int main()
{
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
    }
    vector<bool> used1(n), used2(n);
    vector<int> e1, e2;
    for (int i = 0; i < n; i++) {
        if (!used1[i]) {
            dfs(i, g, used1, e1);
        }
    }
    vector<int> ans; 
    for (int i = n - 1; i >= 0; i--) {
        if (!used2[e1[i]]) {
            dfs(e1[i], g, used2, e2);
            ans.push_back(e1[i]);
        }
    }
    sort(ans.begin(), ans.end());
    for (auto el : ans) {
        cout << el << " ";
    }
    cout << endl;
    
    return 0;
}
