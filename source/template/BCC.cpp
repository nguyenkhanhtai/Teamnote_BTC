const int MAXN = 5e5 + 9;
int n, m;
ii edge[MAXN];
vector<int> g[MAXN];
int used[MAXN], num[MAXN], low[MAXN], sz[MAXN], timeDfs = 0;
vector<vector<int>> bcc;
vector<int> stk;

void dfs(int u, int p){
    stk.pb(u);
    num[u] = low[u] = ++timeDfs;
    sz[u] = 1;
    for(auto id: g[u]){
        int v = edge[id].fi + edge[id].se - u;
        if (used[id]) continue;
        used[id] = true;

        if (!num[v]){

            dfs(v, u);
            sz[u] += sz[v];
            minimize(low[u], low[v]);

            if (low[v] >= num[u]){
                bcc.pb({u});
                while(bcc.back().back() != v){
                    bcc.back().pb(stk.back());
                    stk.pop_back();
                }
            }

        }

        else{
            minimize(low[u], num[v]);
        }
    }

}

-----------------------
//Usage:     
FOR(i, 0, n - 1){
    if (!num[i]) {
        dfs(i, -1);
        if (sz[i] == 1) bcc.pb({i});
    }
}

cout << bcc.size() << endl;
for(auto vt: bcc){
    cout << vt.size() << ' ';
    for(auto x: vt){
        if (x != n) cout << x << ' ';
    }
    cout << endl;
}