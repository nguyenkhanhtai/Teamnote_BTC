const int MAXN = 1e5 + 9;
iii edge[MAXN];
int del[MAXN], sz[MAXN], n;
int answer[MAXN];

vector<int> g[MAXN];
vector<int> listWeight;

int complexity = 0;
void precalc(int u, int p){
    sz[u] = 1;
    for(auto id: g[u]){
        int v = edge[id].se.fi + edge[id].se.se - u;
        if (v == p or del[v]) continue;
        precalc(v, u);
        sz[u] += sz[v];
    }
}

int centroid(int u, int p, int origin){
    for(auto id: g[u]){
        int v = edge[id].se.fi + edge[id].se.se - u;
        if (v == p or del[v]) continue;
        if (sz[v] * 2 > sz[origin]) return centroid(v, u, origin);
    }
    return u;
}

void DnC(int u){
    precalc(u, -1);
    u = centroid(u, -1, u);
    del[u] = true;

    for(auto id: g[u]){
        int v = edge[id].se.fi + edge[id].se.se - u;
        if (del[v]) continue;
        DnC(v);
    }
}