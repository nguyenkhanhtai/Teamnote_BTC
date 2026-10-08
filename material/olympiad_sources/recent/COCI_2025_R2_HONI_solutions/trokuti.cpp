#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n, m; cin >> n >> m;
    int N = 6 * n;
    vector<vector<int>> is_edge(N, vector<int>(N, 0));
    vector<vector<int>> adj(N);
    for (int i = 0; i < m; i++) {
        int a, b; cin >> a >> b; --a; --b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        is_edge[a][b] = is_edge[b][a] = true;
    }

    vector<vector<vector<int>>> where_edge(N, vector<vector<int>>(N));
    vector<vector<pair<int, int>>> edges(N);
    vector<int> is_used(N, 0);

    vector<vector<int>> sol;

    auto add_edge = [&](int a, int b, int v) {
        if (!is_edge[a][v] || !is_edge[b][v] || !is_edge[a][b]) return;
        int dg_a = 0;
        int dg_b = 0;
        if (edges[v].size() > 10) return;
        for (auto e : edges[v]) {
            if (e.first == a || e.second == a) dg_a++;
            if (e.first == b || e.second == b) dg_b++;
        }
        if (dg_a > 3 || dg_b > 3) return;
        edges[v].push_back({a, b});
        where_edge[a][b].push_back(v);
        where_edge[b][a].push_back(v);
    };

    auto rem_edge = [&](int a, int b) {
        for (int v : where_edge[a][b]) {
            for (int i = 0; i < edges[v].size(); ++i) {
                if (edges[v][i] == pair<int, int>(a, b) || edges[v][i] == pair<int, int>(b, a)) {
                    swap(edges[v][i], edges[v].back());
                    edges[v].pop_back();
                    break;
                }
            }
        }
        where_edge[a][b].clear();
        where_edge[b][a].clear();
    };

    auto add_node = [&](int node) {
        is_used[node] = false;
        for (int i : adj[node]) {
            if (!is_used[i]) {
                for (int j : adj[i]) {
                    if (is_edge[node][j]) add_edge(node, i, j);
                }
            }
        }
    };

    auto rem_node = [&](int node) {
        is_used[node] = true;
        for (int i : adj[node]) {
            if (!is_used[i]) rem_edge(node, i);
        }
    };

    for (int i = 0; i < N; i++) {
        for (int j : adj[i]) {
            for (int k : adj[j]) {
                add_edge(i, j, k);
            }
        }
    }


    for (int step = 0; step < n; step++) {
        bool found = false;
        for (int i = 0; i < N; i++) {
            if (is_used[i]) continue;
            if (!edges[i].empty()) {
                vector<int> tr = {i, edges[i][0].first, edges[i][0].second};
                found = true;
                sol.push_back(tr);
                assert(!is_used[tr[0]]);
                assert(!is_used[tr[1]]);
                assert(!is_used[tr[2]]);
                rem_node(tr[0]);
                rem_node(tr[1]);
                rem_node(tr[2]);
                assert(is_edge[tr[0]][tr[1]]);
                assert(is_edge[tr[1]][tr[2]]);
                assert(is_edge[tr[0]][tr[2]]);
                break;
            }
        }
        if (found) continue;
        // assert(false);

        for (int t = 0; t < sol.size(); ++t) {
            if (found) break;
            for (int i = 0; i < 3; ++i) {
                for (int j = i + 1; j < 3; ++j) {
                    if (found) break;
                    int x = sol[t][i];
                    int y = sol[t][j];
                    int z = sol[t][3 - i - j];
                    assert(is_used[x]);
                    assert(is_used[y]);

                    for (auto e1 : edges[x]) {
                        for (auto e2 : edges[y]) {
                            if (found) break;
                            if (e1.first == e2.first || e1.first == e2.second || e1.second == e2.first || e1.second == e2.second) continue;

                            add_node(z);
                            rem_node(e1.first);
                            rem_node(e1.second);
                            rem_node(e2.first); 
                            rem_node(e2.second);

                            vector<int> tr = {e1.first, e1.second, x};
                            vector<int> tr2 = {e2.first, e2.second, y};
                            sol[t] = tr;
                            sol.push_back(tr2);
                            found = true;
                        }
                    }
                }
            }
        }
        assert(found);
    }

    for (auto tr : sol) {
        cout << tr[0] + 1 << " " << tr[1] + 1 << " " << tr[2] + 1 << "\n";
    }
}

int main() {
    int t; cin >> t;
    while (t--) {
        solve();
    }
}