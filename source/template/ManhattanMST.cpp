const int MAXN = 3e5 + 9;
const int INF = 1e18;
int n,s,k; 
struct point{
    int x,y,id;
    int diff_yx(){return y - x;}
    int sum_xy(){return x + y;}
    void rotate_90(){int curx = x, cury = y;x = -cury;y = curx;}
    void flip(){y = -y;}
    bool operator < (const point &other) const{
        if (y == other.y) return x < other.x;
        else return y > other.y;
    }
};
int mahattan(point a,point b){return abs(a.x - b.x) + abs(a.y - b.y);}
struct edge{
    int u,v,w;
    bool operator < (const edge &other) const{ return w < other.w;}
};
edge Edge_From_Point(point u,point v){
    return edge{u.id,v.id,mahattan(u,v)};
}
vector<edge> potential_edges;
vector<point> pt;
struct disjoint_set_union{
    int par[100005],rank[100005];
    disjoint_set_union(int n){
        fill(rank+1,rank+1+n,1);
        iota(par+1,par+1+n,1);
    }
    int root(int u){
        if (par[u] == u) return u;
        else return par[u] = root(par[u]);
    }

    bool unite(int u,int v){
        u = root(u);
        v = root(v);
        if (u!=v){
            if (rank[u] <= rank[v]) swap(u,v);
            rank[u] += rank[v];
            par[v] = u;
            return true;
        }
        return false;
    }
    
};
vector<point> dnc(vector<point> pt){
    if (pt.size() == 1) return pt;
    int mid_size = pt.size() / 2,upper_ptr = 0;
    auto upper = dnc({pt.begin(),pt.begin() + mid_size});
    auto lower = dnc({pt.begin()+mid_size,pt.end()});
    vector<point> res;
    point min_diff_yx{0,INF,-1};

    for(auto lo: lower){
        while(upper_ptr < upper.size() and 
              upper[upper_ptr].sum_xy() <= lo.sum_xy()){
            if (upper[upper_ptr].diff_yx() < min_diff_yx.diff_yx()){
                min_diff_yx = upper[upper_ptr];
            }
            res.pb(upper[upper_ptr]);
            upper_ptr++;
        }
        res.pb(lo);
        if (min_diff_yx.id != -1){
            potential_edges.pb( Edge_From_Point(min_diff_yx,lo));
        }
    }
    res.insert(res.end(),upper.begin() + upper_ptr, upper.end());
    return res;
}
void prepare(){
    sort(pt.begin(),pt.end());
    dnc(pt);
}
void solve(){
    for(int dir=0;dir<2;dir++){
        for(int j=0;j<4;j++){
            prepare();
            for(auto &p: pt){
                p.rotate_90();
            }
        }
        for(auto &p: pt){
            p.flip();
        }
    }

    sort(potential_edges.begin(), potential_edges.end());
    int ans = 0;
    disjoint_set_union DSU(n);
    for(auto e: potential_edges){
        if (DSU.unite(e.u,e.v)){
            if (e.w > s and k > 0) {
               ans += e.w, k--;

            }
        }
    }    
    cout<<ans<<endl;

}

