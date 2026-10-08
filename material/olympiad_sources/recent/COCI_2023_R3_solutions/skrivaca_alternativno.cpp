#include <bits/stdc++.h>
using namespace std;

vector<int> a;
vector<vector<int>> e;
vector<int> winning;

vector<int> dsu, rnk;
int f(int v) {
    if (dsu[v] == v) return v;
    return f(dsu[v]);
}
void Merge(int u, int v, vector<pair<int, int>> &changesDsu, vector<pair<int, int>> &changesRnk) {
    u = f(u);
    v = f(v);

    if (rnk[u] < rnk[v]) swap(u, v) ;
    changesDsu.push_back({v, dsu[v]});
    changesRnk.push_back({u, rnk[u]});

    if (u == v) return;
    dsu[v] = u;
    if (rnk[v] == rnk[u]) rnk[u] ++;
}


void pola_po_pola(int lo, int hi) {
    if (lo + 1 == hi) {
        int u = lo;
        for (int v : e[u]) {
            if (f(a[u]) != f(a[v])) {
                winning.push_back(v);
            }
        }
        return;
    }

    int mi = (lo + hi) >> 1;

    auto MergeOneSideGoTheOther = [&] (int goFrom, int goTo, int mergeFrom, int mergeTo) {
        vector<pair<int, int>> changesDsu, changesRnk;
        for (int u = mergeFrom; u < mergeTo; ++u)
            for (int v : e[u]) if (v < goFrom || v >= goTo)
                Merge(u, v, changesDsu, changesRnk);

        pola_po_pola(goFrom, goTo);

        for (int i = changesDsu.size() - 1; i >= 0; --i) {
            dsu[changesDsu[i].first] = changesDsu[i].second;
            rnk[changesRnk[i].first] = changesRnk[i].second;
        }
        changesDsu.clear();
        changesRnk.clear();
    };

    MergeOneSideGoTheOther(mi, hi, lo, mi);
    MergeOneSideGoTheOther(lo, mi, mi, hi);
}

vector<int> solve(int n) {
    dsu.resize(n);
    rnk.resize(n);
    for (int i = 0; i < n; ++i) dsu[i] = i;

    pola_po_pola(0, n);

    vector<int> sol(n, -1);
    vector<int> visited(n, 0);

    queue<int> bfs;

    for (int u = 0; u < n; ++u) {
        if (a[u] == u) {
            visited[u] = 1;
            sol[u] = 0;
            bfs.push(u);
        }
    }

    for (int u : winning) {
        if (!visited[u]) {
            visited[u] = 1;
            sol[u] = 1;
            bfs.push(u);
        }
    }

    while (!bfs.empty()) {
        int u = bfs.front(); bfs.pop();
        for (int v : e[u]) {
            if (visited[v]) continue;
            sol[v] = sol[u] + 1;
            visited[v] = 1;
            bfs.push(v);
        }
    }

    return sol;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;

    a.resize(n);
    e.resize(n);

    for (int i = 0; i < n; ++i) {
        cin >> a[i]; a[i] --;
    }

    for (int i = 0; i < m; ++i) {
        int u, v; cin >> u >> v;
        u --; v --;

        e[u].push_back(v);
        e[v].push_back(u);
    }

    auto sol = solve(n);

    for (int i = 0; i < n; ++i)
        cout << sol[i] << " ";
    cout << endl;
}
