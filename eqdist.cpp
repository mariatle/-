#include <iostream>
#include <vector>
#include <queue>

using namespace std;



int main()
{
    int n, m, k; cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    cin >> k;
    vector<int> v(k);
    vector<vector<int>> dist(k, vector<int>(n, 0));
    for (int i = 0; i < k; i++) {
        cin >> v[i];
        dist[i][v[i]] = 1;
        queue<int> q;
        q.push(v[i]);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto to : g[u]) {
                if (dist[i][to] == 0) {
                    dist[i][to] = dist[i][u] + 1;
                    q.push(to);
                }
            }
        }
    }
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        bool flag = true;
        for (int j = 1; j < k; j++) {
            if (dist[j][i] != dist[j - 1][i] || dist[j][i] == 0) {
                flag = false;
            }
        }
        if (flag) {
            ans.push_back(i);
        }
    }
    if (ans.empty()) {
        cout << "-" << endl;
    } else {
        for (auto el : ans) {
            cout << el << " "; 
        }
        cout << endl;
    }
    return 0;
}
