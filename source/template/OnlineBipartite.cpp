struct DSU{
    vector<ii> par;
    vector<int> ranking;
    vector<int> bipartite;
    vector<array<int, 6>> update;
    int numComponent = 0;
    int numBipartite = 0;
    DSU(int sz = 0){
        numBipartite = sz;
        numComponent = sz;
        par.resize(sz + 9, ii(-1, 0));
        bipartite.resize(sz + 9, 1);
        ranking.resize(sz + 9, 1);
    }

    ii root(int u){
        if (par[u].fi == -1) return ii(u, 0);
        else{
            ii tmp = root(par[u].fi);
            tmp.se ^= par[u].se;
            return tmp;
        }
    }
    void unite(int u, int v) {
        ii rtu = root(u);
        ii rtv = root(v);
        int rootU = rtu.fi;
        int rootV = rtv.fi;
        int parityU = rtu.se;
        int parityV = rtv.se;
        if (rootU == rootV){
            if (parityU == parityV){
                update.pb({1, numBipartite, rootU, bipartite[rootU]});
                numBipartite -= bipartite[rootU];
                bipartite[rootU] = false;
            }
        }
        else{
            if (ranking[rootU] < ranking[rootV]) swap(rootU, rootV);
            update.pb({2, numBipartite, rootU, bipartite[rootU], rootV, par[rootV].se});
            numBipartite -= bipartite[rootU];
            numBipartite -= bipartite[rootV];
            bipartite[rootU] &= bipartite[rootV];
            numBipartite += bipartite[rootU];
            numComponent--;
            ranking[rootU] += ranking[rootV];
            par[rootV] = ii(rootU, parityU ^ parityV ^ 1);
        }
    }
    void rollback(){
        if (update.size() == 0) return;
        array<int, 6> tp = update.back();
        update.pop_back();
        if (tp[0] == 1){
            numBipartite = tp[1];
            bipartite[tp[2]] = tp[3];
        }
        else{
            numBipartite = tp[1];
            numComponent++;
            bipartite[tp[2]] = tp[3];
            ranking[tp[2]] -= ranking[tp[4]];
            par[tp[4]] = {-1, tp[5]};
        }
    }
};