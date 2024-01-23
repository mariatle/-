#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> g;
vector<vector<string>> w;
vector<bool> used;
vector<int> nums;
int n, m;


void dfs(int v) {
    used[v] = true;
    nums.push_back(v);
    for (auto to : g[v]) {
        if (!used[to]) {
            dfs(to);
        }
    }
}

int main()
{
    int q0; cin >> n >> m >> q0;
    g.resize(n, vector<int>(m));
    w.resize(n, vector<string>(m));
    used.resize(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> g[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> w[i][j];
        }
    }
    
    dfs(q0);
    
    vector<int> new_indexes(n);
    for (int i = 0; i < n; i++) {
        new_indexes[nums[i]] = i;
    }
    cout << n << endl << m << endl << 0 << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << new_indexes[g[nums[i]][j]] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << w[nums[i]][j] << " ";
        }
        cout << endl;
    }
    
    return 0;
}
