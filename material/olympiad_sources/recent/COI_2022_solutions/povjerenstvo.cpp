#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <int, int> pi;

const int MAXN = 500005;

int n, m;
int deg[MAXN], removed[MAXN], bio[MAXN];
vector <int> v[MAXN], r[MAXN], sol, st, curr_comp;
vector < vector <int> > comp;

queue <int> q;

/////////////////////////////////////////////////////////////

void dfs (int node) {
    if (bio[node]) return;
    bio[node] = 1;
    for (auto sus : r[node]) {
        if (!bio[sus]) dfs(sus);
    }
    st.push_back(node);
}

void dfs2 (int node) {
    if (bio[node] == 2) return;
    bio[node] = 2;
    curr_comp.push_back(node);
    for (auto sus : v[node]) {
        if (bio[sus] == 1) dfs2(sus);
    }
}

void kosaraju () {
    for (int i = 1; i <= n; i++) {
        if (!bio[i]) dfs(i);
    }
    while (!st.empty()) {
        int x = st.back();
        st.pop_back();
        if (bio[x] == 2) continue;
        curr_comp.clear();
        dfs2(x);
        comp.push_back(curr_comp);
    }
}

/////////////////////////////////////////////////////////////

void makni (int node, int flg) {
    removed[node] = 1;
    for (auto sus : r[node]) {
        deg[sus]--;
        if (deg[sus] == 0 && flg) q.push(sus);
    }
}

void izaberi (int node, int flg) {
    removed[node] = 1;
    sol.push_back(node);
    for (auto sus : r[node]) {
        if (!removed[sus]) makni(sus, flg);
    }
}

void remove_terminal_nodes (vector <int> nodes) {
    for (auto node : nodes) {
        if (removed[node]) continue;
        if (deg[node] == 0) q.push(node);
    }

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        if (removed[node]) continue;
        izaberi(node, 1);
    }
}

void oboji (int node, int boja) {
    if (bio[node] || removed[node]) return;
    bio[node] = 1;
    if (boja == 0) st.push_back(node);
    for (auto sus : v[node]) oboji(sus, !boja);
    for (auto sus : r[node]) oboji(sus, !boja);
}

void solve_bipartite (vector <int> nodes) {
    st.clear();
    for (auto node : nodes) bio[node] = 0;
    for (auto node : nodes) {
        oboji(node, 0);
    }
    for (auto node : st) {
        izaberi(node, 0);
    }
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        deg[a]++;
        v[a].push_back(b);
        r[b].push_back(a);
    }

    kosaraju();
    for (int i = 0; i < comp.size(); i++) {
        remove_terminal_nodes(comp[i]);
        solve_bipartite(comp[i]);
    }

    cout << sol.size() << endl;
    for (auto x : sol) cout << x << " ";
    return 0;
}
