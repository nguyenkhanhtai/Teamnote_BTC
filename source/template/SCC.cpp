const int MAXN = 5e5 + 9;
int n, m;
ii edge[MAXN];
vector<int> g[MAXN];

int del[MAXN], num[MAXN], low[MAXN], timeDfs = 0;
vector<int> stk;
vector<vector<int>> scc;

void dfs(int u){
    stk.pb(u);
    num[u] = low[u] = ++timeDfs;

    for(auto id: g[u]){
        int v = edge[id].se + edge[id].fi - u;
        if (del[v]) continue;

        if (!num[v]){
            dfs(v);
            minimize(low[u], low[v]);
        }
        else{
            minimize(low[u], num[v]);
        }
    }

    if (low[u] == num[u]){
        int v;
        scc.pb({});
        do{
            v = stk.back();
            stk.pop_back();
            del[v] = true;
            scc.back().pb(v);
        }while(v != u);
    }
}
//Usage:
FOR(i, 0, n - 1){
    if (!num[i]){
        dfs(i);
    }
}

cout << scc.size() << endl;

for(int i = scc.size() - 1; i >= 0; i--){
    cout << scc[i].size() << ' ';
    for(auto x: scc[i]){
        cout << x << ' ';
    }
    cout << endl;