#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <int, int> pi;

const int MAXN = 1000005;

int n, ok = 1;
int x[MAXN], y[MAXN], par[MAXN], siz[MAXN], bio[MAXN], sol[MAXN];
char c[MAXN];
vector <int> sazx, sazy, nodes, edges, lef, rig;
vector <pi> vx[MAXN], vy[MAXN], v[MAXN];

void dsu_init () {
    for (int i = 0; i <= 2*n; i++) {
        par[i] = i;
        siz[i] = 1;
    }
}

int nadi (int a) {
    if (a == par[a]) return a;
    return par[a] = nadi(par[a]);
}

void spoji (int a, int b) {
    a = nadi(a);
    b = nadi(b);
    if (a == b) return;
    if (a > b) swap(a, b);
    par[a] = b;
    siz[b] += siz[a];
}

void sazmi () {
    for (int i = 0; i < n; i++) {
        sazx.push_back(x[i]);
        sazy.push_back(y[i]);
    }
    sort(sazx.begin(), sazx.end());
    sort(sazy.begin(), sazy.end());
    sazx.erase(unique(sazx.begin(), sazx.end()), sazx.end());
    sazy.erase(unique(sazy.begin(), sazy.end()), sazy.end());
    for (int i = 0; i < n; i++) {
        x[i] = lower_bound(sazx.begin(), sazx.end(), x[i]) - sazx.begin();
        y[i] = lower_bound(sazy.begin(), sazy.end(), y[i]) - sazy.begin();
    }
}

void find_cycles () {
    for (int i = 0; i < n; i++) {
        if (c[i] == '/') {
            vx[x[i]].push_back({2 * y[i] + 1, 2 * i + 0});
            vx[x[i]].push_back({2 * y[i] + 0, 2 * i + 1});
            vy[y[i]].push_back({2 * x[i] + 0, 2 * i + 0});
            vy[y[i]].push_back({2 * x[i] + 1, 2 * i + 1});
        } else {
            vx[x[i]].push_back({2 * y[i] + 1, 2 * i + 0});
            vx[x[i]].push_back({2 * y[i] + 0, 2 * i + 1});
            vy[y[i]].push_back({2 * x[i] + 1, 2 * i + 0});
            vy[y[i]].push_back({2 * x[i] + 0, 2 * i + 1});
        }
    }
    for (int i = 0; i < sazx.size(); i++) {
        sort(vx[i].begin(), vx[i].end());
        for (int j = 1; j + 1 < vx[i].size(); j += 2) {
            spoji(vx[i][j].second, vx[i][j + 1].second);
        }
        spoji(vx[i][0].second, 2 * n);
        spoji(vx[i].back().second, 2 * n);
    }
    for (int i = 0; i < sazy.size(); i++) {
        sort(vy[i].begin(), vy[i].end());
        for (int j = 1; j + 1 < vy[i].size(); j += 2) {
            spoji(vy[i][j].second, vy[i][j + 1].second);
        }
        spoji(vy[i][0].second, 2 * n);
        spoji(vy[i].back().second, 2 * n);
    }
}

void build_graph () {
    for (int i = 0; i <= 2 * n; i++) {
        if (i == par[i]) {
            nodes.push_back(i);
            if (i < 2 * n && siz[i] % 8 != 0) ok = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        int a = nadi(2 * i);
        int b = nadi(2 * i + 1);
        v[a].push_back({b, i});
        v[b].push_back({a, i});
    }
}

void euler (int x) {
    while (v[x].size()) {
        int to = v[x].back().first;
        int ind = v[x].back().second;
        v[x].pop_back();
        if (bio[ind]) continue;
        bio[ind] = 1;
        euler(to);
        edges.push_back(ind);
    }
}

void solve () {
    euler(2 * n);
    for (int i = 0; i < edges.size(); i++) {
        if (i % 2 == 0) lef.push_back(edges[i]);
        if (i % 2 == 1) rig.push_back(edges[i]);
    }
    edges.clear();
    memset(bio, 0, sizeof bio);

    for (auto i : lef) {
        int a = nadi(2 * i);
        int b = nadi(2 * i + 1);
        v[a].push_back({b, i});
        v[b].push_back({a, i});
    }
    for (int i = (int)nodes.size() - 1; i >= 0; i--) {
        euler(nodes[i]);
    }
    for (int i = 0; i < edges.size(); i++) {
        sol[edges[i]] = 1 + i % 2;
    }
    edges.clear();
    memset(bio, 0, sizeof bio);

    for (auto i : rig) {
        int a = nadi(2 * i);
        int b = nadi(2 * i + 1);
        v[a].push_back({b, i});
        v[b].push_back({a, i});
    }
    for (int i = (int)nodes.size() - 1; i >= 0; i--) {
        euler(nodes[i]);
    }
    for (int i = 0; i < edges.size(); i++) {
        sol[edges[i]] = 3 + i % 2;
    }
    edges.clear();
    memset(bio, 0, sizeof bio);
}

void ispis () {
    for (int i = 0; i < n; i++) {
        cout << sol[i] << " ";
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    dsu_init();
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i] >> c[i];
    }
    sazmi();
    find_cycles();
    build_graph();
    if (!ok) {
        cout << "-1";
        return 0;
    }
    solve();
    ispis();
    return 0;
}
