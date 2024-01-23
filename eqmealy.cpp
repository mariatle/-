#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_set>

using namespace std;


struct MealyMachine {
    int n, m;
    int q0;
    vector<vector<int>> g;
    vector<vector<string>> w;
};

inline void MinMealy(MealyMachine & mealy) {
    int n = mealy.n, m = mealy.m;
    
    
    vector<vector<vector<int>>> inv(n, vector<vector<int>>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            inv[mealy.g[i][j]][j].push_back(i);
        }
    }
    
    vector<unordered_set<int>> all;
    vector<int> ind(n, -1);
    
    vector<pair<vector<string>, int>> st;
    for (int i = 0; i < n; i++) {
        st.emplace_back(mealy.w[i], i);
    }
    sort(st.begin(), st.end());
    unordered_set<int> cur;
    for (int i = 0; i < n; i++) {
        
        cur.insert(st[i].second);
        ind[st[i].second] = all.size(); 
        if (i == n - 1 || st[i].first != st[i + 1].first) {
            all.push_back(cur);
            cur.clear();
        }
    }

    
    queue<int> q;
    for (int i = 0; i < all.size(); i++) {
        q.push(i);
    }


    
    vector<int> count(n), twin(n);
    while (q.size()) {
        int i = q.front();
        q.pop();
        for (int c = 0; c < m; c++) {
            vector<int> involved;
            for (int j : all[i]) {
                for (int r : inv[j][c]) {
                    int id = ind[r];
                    if (!count[id]) {
                        involved.push_back(id);
                    }
                    count[id]++;
                }
            }
            
            for (int j : involved) {
                if (count[j] != all[j].size()) {
                    twin[j] = all.size();
                    all.push_back({});
                } else {
                    twin[j] = -1;
                }
            }

            for (int j : all[i]) {
                for (int r : inv[j][c]) {
                    int id = ind[r];
                    if (twin[id] != -1) {
                        all[id].erase(r);
                        all[twin[id]].insert(r);
                        ind[r] = twin[id];
                    }
                    count[id]--;
                }
            }

            for (int j : involved) {
                if (twin[j] != -1) {
                    if (all[j].size() < all[twin[j]].size()) {
                        q.push(j);
                    } else {
                        q.push(twin[j]);
                    }
                }
            }
        }
    }

    vector<vector<int>> ng(all.size(), vector<int>(m));
    vector<vector<string>> nw(all.size(), vector<string>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ng[ind[i]][j] = ind[mealy.g[i][j]];
            nw[ind[i]][j] = mealy.w[i][j];
        }
    }
    mealy.n = all.size();
    mealy.q0 = ind[mealy.q0];
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

bool EqMealy(MealyMachine & mealy1, MealyMachine & mealy2) {
    if (mealy1.n != mealy2.n || mealy2.m != mealy2.m || mealy1.q0 != mealy2.q0) {
        return false;
    }
    for (int i = 0; i < mealy1.n; i++) {
        for (int j = 0; j < mealy1.m; j++) {
            if (mealy1.g[i][j] != mealy2.g[i][j] || mealy1.w[i][j] != mealy2.w[i][j]) {
                return false;
            }
        }
    }
    return true;
}


int main()
{
    MealyMachine mealy1, mealy2;
    Read(mealy1);
    Read(mealy2);
    MinMealy(mealy1);
    Canonic(mealy1);
    MinMealy(mealy2);
    Canonic(mealy2);
    if (EqMealy(mealy1, mealy2)) {
        cout << "EQUAL" << endl;
    } else {
        cout << "NOT EQUAL" << endl;
    }
    return 0;
}
