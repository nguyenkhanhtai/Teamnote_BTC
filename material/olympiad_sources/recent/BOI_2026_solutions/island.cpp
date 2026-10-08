#include <iostream>
#include <vector>

using namespace std;

const int N = 1010;
string g[N];
int a[2][N][N];

struct tree {
    int n, k = 0;
    vector<vector<int>> adj;
    vector<vector<int>> jmp;
    vector<int> p, d;
    
    void dfs(int u) {
        d[u] = d[p[u]] + 1;
        for (int v : adj[u]) {
            if (v != p[u]) {
                p[v] = u;
                dfs(v);
            }
        }
    }
    
    tree() {}
    
    tree(int _n, vector<pair<int, int>> &e) : n(_n) {
        ++n;
        while ((1 << k) < 2*n) ++k;
        
        adj.resize(n);
        p.resize(n, 0);
        d.resize(n, 0);
        
        jmp.resize(k, vector<int>(n));
        
        for (auto [u, v] : e) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        
        dfs(1);
        
        for (int i = 0; i < n; ++i) jmp[0][i] = p[i];
        
        for (int j = 1; j < k; ++j) {
            for (int i = 0; i < n; ++i)
                jmp[j][i] = jmp[j-1][jmp[j-1][i]];
        }
    }
    
    int lca(int u, int v) {
        if (u == v) return u;
        if (d[u] < d[v]) swap(u, v);
        
        for (int j = k-1; j >= 0; --j)
            if (d[jmp[j][u]] >= d[v])
                u = jmp[j][u];
        
        if (u == v) return u;
        for (int j = k-1; j >= 0; --j) {
            if (jmp[j][u] != jmp[j][v]) {
                u = jmp[j][u];
                v = jmp[j][v];
            }
        }
        return p[u];
    }
    
    int dis(int u, int v) {
        return d[u] + d[v] - 2*d[lca(u, v)];
    }
};

int main() {
    cin.tie(0) -> sync_with_stdio(0);
    
    int n, q;
    cin >> n >> q;
    
    for (int i = 0; i < n; ++i) {
        cin >> g[i];
    }
    
    vector<pair<int, int>> e[2];
    tree tr[2];
    int w[2]{};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (g[i][j] == '#') {
                if (i == 0 || g[i-1][j] == '.')
                    a[0][i][j] = ++w[0];
                else
                    a[0][i][j] = a[0][i-1][j];
                if (j > 0 && g[i][j-1] == '#' && (i == 0 || g[i-1][j] == '.' || g[i-1][j-1] == '.'))
                    e[0].push_back({a[0][i][j], a[0][i][j-1]});
                
                if (j == 0 || g[i][j-1] == '.')
                    a[1][i][j] = ++w[1];
                else
                    a[1][i][j] = a[1][i][j-1];
                if (i > 0 && g[i-1][j] == '#' && (j == 0 || g[i][j-1] == '.' || g[i-1][j-1] == '.'))
                    e[1].push_back({a[1][i][j], a[1][i-1][j]});
            }
        }
    }
    
    for (int k = 0; k < 2; ++k)
        tr[k] = tree(w[k], e[k]);
    
    for (int i = 0; i < q; ++i) {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        --r1;--c1;--r2;--c2;
        
        int ans = 0;
        for (int k = 0; k < 2; ++k)
            ans += tr[k].dis(a[k][r1][c1], a[k][r2][c2]);
        
        cout << ans << '\n';
    }
}
