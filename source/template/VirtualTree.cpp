int n, m;
const int MAXN = 7e5 + 9;
vector<int> g[MAXN];
vector<int> container[MAXN];
vector<ii> VT[MAXN];
vector<int> eulerPath;
ii h[30][MAXN];
int in[MAXN], out[MAXN], cnt[MAXN], dfsTime = 0;
int depth[MAXN], a[MAXN], dp[MAXN], sz[MAXN];
void dfs(int u, int p, int d){
    if (p == -1) dfsTime = 0;
    in[u] = eulerPath.size();
    depth[u] = d;
    eulerPath.pb(u);
    for(auto v: g[u]){
        if (v == p) continue;
        dfs(v, u, d + 1);
        eulerPath.pb(u);
    }
    out[u] = eulerPath.size();
}
bool inSubtree(int u, int v){
    //Return if v is in the subtree of u.
    return in[v] >= in[u] && in[v] < out[u];
}
ii getLCA(int u, int v){
    int l = in[u]; 
    int r = in[v];
    if (l > r) swap(l, r);
    int x = log2(r - l + 1);
    return min(h[x][l], h[x][r - (1 << x) + 1]);
}
void buildLCA(){
    FOR(i, 0, sz(eulerPath) - 1){
        h[0][i] = {depth[eulerPath[i]], eulerPath[i]};
    }
    FOR(i, 1, 20){
        for(int j = 0; j + (1 << i) - 1 < sz(eulerPath); j++){
            h[i][j] = min(h[i - 1][j], h[i - 1][j + (1 << (i - 1))]);
        }
    }
}
int getDist(int u, int v){
    int lca = getLCA(u, v).se;
    return depth[u] + depth[v] - 2 * depth[lca];
}
void buildVT(vector<int> &container, int cnt){
    if (sz(container) == 0) return 0;
    sort(container.begin(), container.end(), [&](const int &a, const int &b){
         return in[a] < in[b];
    });
    vector<int> stk;
    int m = sz(container);
    int inv = binpow(m, MOD - 2);
    FOR(i, 0, m - 1){
        sz[container[i]] = 1;
    }
    FOR(i, 0, m - 2){
        container.pb(getLCA(container[i], container[i + 1]).se);
    }
    sort(container.begin(), container.end(), [&](const int &a, const int &b){
         return in[a] < in[b];
    });
    container.erase(unique(container.begin(), container.end()), container.end());

    m = sz(container);

    FOR(i, 0, m - 1){
        if (stk.empty()){
            stk.pb(container[i]);
        }
        else{
            while(!stk.empty() and !inSubtree(stk.back(), container[i]))
                stk.pop_back();            
            VT[stk.back()].pb({container[i], getDist(stk.back(), container[i])});
            stk.pb(container[i]);
        }
    }

    int sum = 0;
    //Do something with Virtual Tree

    FOR(i, 0, sz(container) - 1){
        sz[container[i]] = 0;
        dp[container[i]] = 0;
        VT[container[i]].clear();
    }
}
