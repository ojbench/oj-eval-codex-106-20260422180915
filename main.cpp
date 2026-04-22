#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; long long k;
    if (!(cin >> n >> k)) return 0;
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    // Root the tree at 1 iteratively to avoid recursion limits
    vector<int> parent(n + 1, 0);
    vector<int> order; order.reserve(n);
    order.push_back(1);
    parent[1] = 0;
    for (size_t idx = 0; idx < order.size(); ++idx) {
        int u = order[idx];
        for (int v : g[u]) if (v != parent[u]) {
            parent[v] = u;
            order.push_back(v);
        }
    }

    vector<int> sub(n + 1, 1);
    for (int i = (int)order.size() - 1; i >= 0; --i) {
        int u = order[i];
        for (int v : g[u]) if (v != parent[u]) sub[u] += sub[v];
    }

    vector<int> ans; ans.reserve(n);
    for (int u = 1; u <= n; ++u) {
        long long max_comp = 0;
        for (int v : g[u]) {
            if (v == parent[u]) {
                long long up = (long long)n - sub[u];
                if (up > max_comp) max_comp = up;
            } else {
                if ((long long)sub[v] > max_comp) max_comp = sub[v];
            }
        }
        if (max_comp <= k) ans.push_back(u);
    }

    if (ans.empty()) {
        cout << "None\n";
    } else {
        sort(ans.begin(), ans.end(), greater<int>());
        for (size_t i = 0; i < ans.size(); ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}
