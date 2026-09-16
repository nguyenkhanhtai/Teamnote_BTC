vector<int> g[MAXN];
ii edge[MAXN];
int n, m;
int processed[MAXN], h[MAXN], par[MAXN], used[MAXN];
void DirectedDfs(int u){
processed[u] = 1;
for(auto id: g[u]){
int v = edge[id].fi + edge[id].se - u;
if (processed[v] == 1){
    cout << h[u] - h[v] + 1<< endl;
    vector<int> ans;
    ans.pb(id);
    int tmp = u;
    while(tmp != v){
        ans.pb(par[tmp]);
        tmp = edge[par[tmp]].se + edge[par[tmp]].fi - tmp;
    }
    reverse(ans.begin(), ans.end());
    for(auto x: ans){
        cout << x << endl;
    }
    exit(0);
}

if (processed[v] == 0){
    h[v] = h[u] + 1;
    par[v] = id;
    DirectedDfs(v);
}
}

processed[u] = 2;
}

int num[MAXN], depth[MAXN], low[MAXN], timeDfs = 0;
vector<int> ansE, ansV;

void undirectedDfs(int u){
num[u] = low[u] = ++timeDfs;
for(auto id: g[u]){
int v = edge[id].se + edge[id].fi - u;
if (used[id]) continue;
used[id] = true;

if(!num[v]){
    depth[v] = depth[u] + 1;
    par[v] = id;
    undirectedDfs(v);
    minimize(low[u], low[v]);
}
else{
    ansV.pb(u);
    ansE.pb(id);
    int tmp = u;
    while(tmp != v){
        ansE.pb(par[tmp]);
        ansV.pb(edge[par[tmp]].se + edge[par[tmp]].fi - tmp);
        tmp = ansV.back();
    }
    reverse(ansE.begin(), ansE.end());
    reverse(ansV.begin(), ansV.end());
    cout << ansV.size() << endl;
    for(auto v: ansV) cout << v << ' ';
    cout << endl;
    for(auto e: ansE) cout << e << ' ';
    exit(0);
}
}
}