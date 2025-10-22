struct MF{
    struct edge{
        int to, rev, flow, cap;
    };
 
    vector<int> dist, work;
    vector<vector<edge>> g;
    queue<int> q;
    int numVertex, source, sink;
 
    void addEdge(int u, int v, int cap){
        edge b = {v, g[v].size(), 0, cap};
        edge a = {u, g[u].size(), 0, 0};
//        printf("%lld %lld %lld\n", u, v, cap);
        g[u].pb(b);
        g[v].pb(a);
    }
 
    bool bfs(int threshold){
        FOR(i, source, sink){
            dist[i] = -1;
        }
        q.push(source);
        dist[source] = 0;
 
        while(!q.empty()){
            int u = q.front();
            q.pop();
 
            for(auto e: g[u]){
                int v = e.to;
                if (e.cap - e.flow >= threshold and dist[v] == -1){
                    dist[v] = dist[u] + 1;
                    q.push(v);
                }
            }
        }
        return dist[sink] != -1;
    }
 
    int dfs(int u, int f){
        if (u == sink) return f;
        for(int &s = work[u]; s < g[u].size(); s++){
            auto &e = g[u][s];
            int v = e.to;
            if (e.flow < e.cap /*e.flow < e.cap la vo cung quan trong */
                and dist[v] == dist[u] + 1){
                int mf = dfs(v, min(f, e.cap - e.flow));
                if (mf > 0){
                    e.flow += mf;
                    g[v][e.rev].flow -= mf;
                    return mf;
                }
            }
        }
        return 0;
    }
 
    void init(int sz = 0){
        numVertex = sz;
        g.resize(numVertex + 9);
        dist.resize(numVertex + 9, 0);
        work.resize(numVertex + 9, 0);
 
    }
 
    int maxFlow(){
        int ans = 0;
        FORD(i, 20, 0){
            while(bfs((1 << i))){
                fill(work.begin(), work.begin() + numVertex - 1, 0);
                while(int res = dfs(source, 1e18)) ans += res;
            }
        }
        return ans;
    }
};