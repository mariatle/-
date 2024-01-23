#include <iostream>
#include <vector>

using namespace std;

template<typename T>
struct Heap {
    void insert(const T & el) {
        int ind = heap.size();
        heap.push_back(el);
        while (ind > 0) {
            if (heap[(ind - 1) / 2] <= heap[ind]) {
                break;
            }
            swap(heap[(ind - 1) / 2], heap[ind]);
            ind = (ind - 1) / 2;
        }
    }
    T begin() {
        return heap[0];
    }
    void erase() {
        if (heap.empty()) {
            return;
        }
        int ind = heap.size() - 1;
        swap(heap[ind], heap[0]);
        heap.pop_back();
        ind = 0;
        while (ind < heap.size()) {
            int lind = 2 * ind + 1, rind = 2 * ind + 2;
            int nind = lind;
            if (rind < heap.size() && heap[rind] < heap[lind]) {
                nind = rind;
            }
            if (nind < heap.size() && heap[ind] > heap[nind]) {
                swap(heap[ind], heap[nind]);
                ind = nind;
            } else {
                break;
            }
        }
        return;
    }
    bool empty() {
        return heap.empty();
    }

private:
    vector<T> heap;
};

int main() {
    int n, m; cin >> n >> m;
    vector<vector<pair<int, long long>>> g(n);
    vector<bool> used(n, false);
    for (int i = 0; i < m; i++) {
        int u, v; long long w;
        cin >> u >> v >> w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    long long sum = 0;
    Heap<pair<long long, pair<int, int>>> st;
    used[0] = true;
    for (auto [to, w] : g[0]) {
        st.insert(make_pair(w, make_pair(0, to)));
    }
    while (!st.empty()) {
        pair<long long, pair<int, int>> b = st.begin();
        if (used[b.second.second]) {
            st.erase();
            continue;
        }
        int nv = b.second.second;
        sum += b.first;
        for (auto [to, w] : g[nv]) {
            if (!used[to]) {
                st.insert(make_pair(w, make_pair(nv, to)));
            }
        }
        used[nv] = true;
    }
    cout << sum << endl;
    return 0;
}
