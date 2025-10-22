const int MAXN = 2e5 + 9;
vector<int> g[MAXN];
int a[MAXN], b[MAXN], n, q;
ii line[MAXN];

int sz[MAXN], depth[MAXN], par[MAXN];


struct Node{  
    //The sample node from vertex set composite sum
    ii fromLeft;
    ii fromRight;
    Node operator + (const Node &other){
         Node res;
         res.fromLeft = fromLeft + other.fromLeft;
         res.fromRight = other.fromRight + fromRight;
         return res;
    }
    Node(){
        fromLeft = {1, 0};
        fromRight = {1, 0};
    }
};

struct HLD{ //Data Structure For HLD
    vector<ii> chain;
    vector<Node> st;
    void init(int sz){
        st.resize(sz * 4 + 9);
    }

    void build(int node,int l,int r){
        if (l == r){
            st[node].fromLeft = st[node].fromRight = chain[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(node << 1, l, mid);
        build(node << 1 | 1, mid + 1, r);
        st[node] = st[node << 1] + st[node << 1 | 1];
    }

    void update(int node,int l,int r,int pos,int c,int d){
        if (l == r){
            st[node].fromLeft = st[node].fromRight = {c, d};
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid) update(node << 1,l, mid, pos, c, d);
        else update(node << 1 | 1, mid + 1, r , pos, c, d);
        st[node] = st[node << 1] + st[node << 1 | 1];
    }

    Node get(int node,int l,int r,int u,int v){

        if (l >= u and r <= v){
            return st[node];
        }

        if (l > v or r < u) return Node();
        int mid = (l + r) >> 1;
        return get(node << 1, l, mid, u, v) + get(node << 1 | 1, mid + 1, r, u, v);
    }

    Node get(int u,int v){
        return get(1, 0, chain.size() - 1, u, v);
    }

    void update(int pos,int c,int d){
        update(1, 0, chain.size() - 1, pos, c, d);
    }
};

HLD opt[MAXN];
int PosOnChain[MAXN], HeadChain[MAXN], IdChain[MAXN], NumChain;
void precalc(int u,int p){
    par[u] = p;
    depth[u] = 1;
    if (p != -1) depth[u] = depth[p] + 1;
    for(auto v: g[u]){
        if (v == p) continue;
        precalc(v, u);
        sz[u] += sz[v];
    }
}

void buildHLD(int u,int p,int curchain){
     PosOnChain[u] = opt[curchain].chain.size();
     IdChain[u] = curchain;
     if (PosOnChain[u] == 0) HeadChain[curchain] = u;
     opt[curchain].chain.pb(line[u]);

     int bigchild = -1;
     for(auto v: g[u]){
        if (v == p) continue;
        if (bigchild == -1 or sz[bigchild] < sz[v]){
            bigchild = v;
        }
     }

     if (bigchild != -1) buildHLD(bigchild, u, curchain);

     for(auto v: g[u]){
         if (v == p or v == bigchild) continue;
         buildHLD(v, u, ++NumChain);
     }
}

void updateNode(int p,int c,int d){
     opt[IdChain[p]].update(PosOnChain[p], c, d);
}

ii getpath(int u,int v){
    Node p1;
    Node p2;
    while(IdChain[u] != IdChain[v]){
          //In case order doesn't matter, you can swap to make things easier
          if(depth[HeadChain[IdChain[u]]] > depth[HeadChain[IdChain[v]]]){
            p1 = opt[IdChain[u]].get(0, PosOnChain[u]) + p1;
            u = par[HeadChain[IdChain[u]]];
          }
          else{
            p2 = opt[IdChain[v]].get(0, PosOnChain[v]) + p2;
            v = par[HeadChain[IdChain[v]]];
          }
    }

    //query the remaining part
    if (depth[u] <= depth[v]){
        return (p2.fromRight
                + opt[IdChain[u]].get(PosOnChain[u], PosOnChain[v]).fromRight
                + p1.fromLeft);
    }
    else{
        return (p2.fromRight
                + opt[IdChain[u]].get(PosOnChain[v], PosOnChain[u]).fromLeft
                + p1.fromLeft);
    }
}