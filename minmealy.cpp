#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int maxn = 3e3;

struct MealyMachine {
    int n, m;
    int q0;
    vector<vector<int>> g;
    vector<vector<string>> w;
};


inline void MinMealy(MealyMachine & mealy) {
    vector<vector<vector<int>>> tg(mealy.n, vector<vector<int>>(mealy.m));
    for (int i = 0; i < mealy.n; i++) {
        for (int j = 0; j < mealy.m; j++) {
            tg[mealy.g[i][j]][j].push_back(i);
        }
    }
    queue<int> q;
    vector<vector<char>> n_eq(mealy.n, vector<char>(mealy.n));
    for (int i = 0; i < mealy.n; i++) {
        for (int j = 0; j < i; j++) {
            for (int c = 0; c < mealy.m; c++) {
                if (mealy.w[i][c] != mealy.w[j][c] && !n_eq[i][j]) {
                    n_eq[i][j] = true;
                    n_eq[j][i] = true;
                    q.push(i * maxn + j);
                }
            }
        }
    }
    while (!q.empty()) {
        int p = q.front();
        int x = p / maxn, y = p % maxn;
        q.pop();
        for (int c = 0; c < mealy.m; c++) {
            for (auto u : tg[x][c]) {
                for (auto v : tg[y][c]) {
                    if (!n_eq[u][v]) {
                        q.push(u * maxn + v);
                        n_eq[u][v] = true;
                        n_eq[v][u] = true;
                    }
                }
            }
        }
    }
    vector<int> new_indexes(mealy.n, -1);
    int cnt = 0;
    for (int i = 0; i < mealy.n; i++) {
        for (int j = 0; j < i; j++) {
            if (!n_eq[i][j]) {
                new_indexes[i] = new_indexes[j];
                break;
            }
        }
        if (new_indexes[i] == -1) {
            new_indexes[i] = cnt;
            cnt++;
        }
    }
    vector<vector<int>> ng(cnt, vector<int>(mealy.m));
    vector<vector<string>> nw(cnt, vector<string>(mealy.m));
    for (int i = 0; i < mealy.n; i++) {
        for (int j = 0; j < mealy.m; j++) {
            ng[new_indexes[i]][j] = new_indexes[mealy.g[i][j]];
            nw[new_indexes[i]][j] = mealy.w[i][j];
        }
    }
    mealy.n = cnt;
    mealy.q0 = new_indexes[mealy.q0];
    mealy.g = ng;
    mealy.w = nw;
    return;
}


void dfs(int v, vector<vector<int>> & g, vector<bool> & used, vector<int> & nums) {
    used[v] = true;
    nums.push_back(v);
    for (auto to : g[v]) {
        if (!used[to]) {
            dfs(to,g, used, nums);
        }
    }
}

inline void Canonic(MealyMachine & mealy) {
    vector<bool> used(mealy.n);
    vector<int> nums;
    
    dfs(mealy.q0, mealy.g, used, nums);
    
    vector<vector<int>> ng(nums.size(), vector<int>(mealy.m));
    vector<vector<string>> nw(nums.size(), vector<string>(mealy.m));
    
    vector<int> new_indexes(mealy.n);
    for (int i = 0; i < nums.size(); i++) {
        new_indexes[nums[i]] = i;
    }
    for (int i = 0; i < nums.size(); i++) {
        for (int j = 0; j < mealy.m; j++) {
            ng[i][j] = new_indexes[mealy.g[nums[i]][j]];
            nw[i][j] = mealy.w[nums[i]][j];
        }
    }
    mealy.n = nums.size();
    mealy.q0 = 0;
    mealy.g = ng;
    mealy.w = nw;
}



inline void Print(MealyMachine & mealy) {
    printf("digraph {\n");
    printf("   rankdir = LR\n");
    for (int i = 0; i < mealy.n; i++) {
        for (int j = 0; j < mealy.m; j++) {
            char s[10];
            for (int t = 0; t < mealy.w[i][j].size(); t++) {
                s[t] = mealy.w[i][j][t];
            }
            s[mealy.w[i][j].size()] = '\0';
            printf("   %d -> %d [label=\"%c(%s)\"]\n", i, mealy.g[i][j], 'a' + j, s);    
        }
    }
    printf("}\n");
}

inline void Read(MealyMachine & mealy) {
    scanf("%d", &mealy.n);
    scanf("%d", &mealy.m);
    scanf("%d", &mealy.q0);
    mealy.g.resize(mealy.n, vector<int>(mealy.m));
    mealy.w.resize(mealy.n, vector<string>(mealy.m));
    for (int i = 0; i < mealy.n; i++) {
        for (int j = 0; j < mealy.m; j++) {
            scanf("%d", &mealy.g[i][j]);
        }
    }
    for (int i = 0; i < mealy.n; i++) {
        for (int j = 0; j < mealy.m; j++) {
            char s[10];
            scanf("%s", s);
            mealy.w[i][j] = s;
        }
    }
}


int main()
{
    MealyMachine mealy;
    Read(mealy);
    MinMealy(mealy);
    Canonic(mealy);
    Print(mealy);
    return 0;
}
