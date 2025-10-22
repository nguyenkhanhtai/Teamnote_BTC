struct DSU{
    vector<int> ranking, par;
    vector<ii> changes;
    int numComp = 0;
    int small_to_large;
    int path_compression;
    int roll_back;
    
    DSU(int sz = 0, int _small_to_large = 1, int _path_compression = 1, int _roll_back = 0){
        ranking.resize(sz + 9, 1);
        par.resize(sz + 9, 0);
        iota(par.begin(), par.end(), 0);
        numComp = sz;
        small_to_large = _small_to_large;
        path_compression = _path_compression;
        roll_back = _roll_back;
    }
 
    void rollback(){
        if (changes.size() == 0) return;
        ii tp = changes.back();
        int u =tp.fi, v = tp.se;
        ranking[u] -= ranking[v];
        par[v] = v;
        numComp++;
        changes.pop_back();
    }
 
    int root(int u){
        if (par[u] == u) return u;
        else{
            if (path_compression) return par[u] = root(par[u]);
            else return root(par[u]);
        }
    }
 
    bool unite(int u, int v){
        u = root(u);
        v = root(v);
        if (u != v){
            if (small_to_large and ranking[u] < ranking[v]) swap(u, v);
            ranking[u] += ranking[v];
            par[v] = u;
            numComp--;
            if (roll_back) changes.pb(ii(u, v));
            return true;
        }
        return false;
    }
 
};
vector<ii> segtree[MAXN << 2];
 
void addEdge(int nn, int l, int r, int u, int v, ii e){
    if (l >= u and r <= v){
        segtree[nn].pb(e);
        return;
    }
    if (l > v or r < u) return;
    int mid = (l + r) >> 1;
    addEdge(nn << 1, l, mid, u, v, e);
    addEdge(nn << 1 | 1, mid + 1, r, u, v, e);
}
 
DSU D;
void go(int nn, int l, int r){
    int oldSz = D.changes.size();
    for(auto e: segtree[nn]){
        D.unite(e.fi, e.se);
    }
 
    if (l == r){
        cout << D.numComp << endl;
    }
    else{
        int mid = (l + r) >> 1;
        go(nn << 1, l, mid);
        go(nn << 1 | 1, mid + 1, r);
    }
 
    while(D.changes.size() > oldSz){
        D.rollback();
    }
}
 
map<ii, int> lastTime;
int n , m, q;