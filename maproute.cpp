#include <iostream>
#include <vector>
#include <set>

using namespace std;



int main()
{
    int n; cin >> n;
    vector<vector<int>> mp(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> mp[i][j];
        }
    }
    vector<vector<int>> g(n * n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i > 0) {
                g[i * n + j].push_back((i - 1) * n + j);
            }
            if (j > 0) {
                g[i * n + j].push_back(i * n + j - 1);
            }
            if (i < n - 1) {
                g[i * n + j].push_back((i + 1) * n + j);
            }
            if (j < n - 1) {
                g[i * n + j].push_back(i * n + j + 1);
            }
        }
    }
    int inf = 1e9;
    vector<int> dist(n * n, inf);
    set<pair<int, int>> st;
    dist[0] = mp[0][0];
    st.insert(make_pair(dist[0], 0));
    while (!st.empty()) {
        pair<int, int> b = *st.begin();
        st.erase(st.begin());
        int u = b.second, d = b.first;
        for (auto to : g[u]) {
            int i = to / n, j = to % n;
            if (d + mp[i][j] < dist[to]) {
                if (dist[to] != inf) {
                    st.erase(make_pair(dist[to], to));
                }
                dist[to] = d + mp[i][j];
                st.insert(make_pair(dist[to], to));
            }
        }
    }
    cout << dist[(n - 1) * n + n - 1];
    return 0;
}
