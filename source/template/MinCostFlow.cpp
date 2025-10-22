bool maximize(int &a, int b){
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}
 
bool minimize(int &a, int b){
    if (a > b){
        a = b;
        return true;
    }
    return false;
}
struct MCMF{
    int sz;
    int source, sink;
    struct Edge{
        int to, rev, flow, cap, cost;
    };
    vector<vector<Edge>> g;
    vector<int> trace, dist, p, visited, inqueue;
    int val, ans = 0;
    void addEdge(int u, int v, int cap, int cost){
        Edge a = {v, g[v].size(), 0, cap, cost};
        Edge b = {u, g[u].size(), 0, 0, -cost};
        // cout << u << ' ' << v << ' ' << cap << ' ' <<cost << endl;
        g[u].pb(a);
        g[v].pb(b);
    }
 
    queue<int> pq;
    MCMF(int n = 0, int _val = 0){
        source = 0;
        sink = n + 1;
        sz = n + 10;
        val = _val;
        inqueue.resize(sz + 1);
        g.resize(sz + 1);
        trace.resize(sz + 1);
        dist.resize(sz + 1);
        p.resize(sz + 1);
        visited.resize(sz + 1);
    }
    bool fbm(){
        for(int i=source;i<=sink;i++){
            dist[i] = INF;
            trace[i] = 0;
            visited[i] = 0;
        }
        dist[source] = 0;
        pq.push(source);
        while(!pq.empty()){
            int u = pq.front();
            inqueue[u] = false;
            pq.pop();
            for(auto e: g[u]){
                if (e.flow < e.cap){
                    if (dist[e.to] > dist[u] + e.cost){
                        dist[e.to] = dist[u] + e.cost;
                        trace[e.to] = e.rev;
 
                        if (!inqueue[e.to]){
                            pq.push(e.to);
                        }
                    }
                }
            }
        }
        return dist[sink] < INF;
    }
    
    int inc(){
        int del = INF;
        for (int i=sink;i!=source;){
            int idEdge = trace[i];
            int prvNode = g[i][idEdge].to;
            int prvEdge = g[i][idEdge].rev;
            minimize(del, g[prvNode][prvEdge].cap - g[prvNode][prvEdge].flow);
 
            i = prvNode;
        }
        del = min(del, val);
        for(int i = sink; i != source;){
            int idEdge = trace[i];
            int prvNode = g[i][idEdge].to;
            int prvEdge = g[i][idEdge].rev;
            g[prvNode][prvEdge].flow += del;
            g[i][idEdge].flow -= del;
            i = prvNode;
        }
 
        int ans = dist[sink] * del;
        val -= del;
        // cout << dist[sink] - p[source] + p[sink] << endl;
        // cout << del << ' ' << val << ' ' << (dist[sink] - p[source] + p[sink]) * del << endl;
 
        return ans;
    }
    int run(){
        while(fbm() and val > 0){
            ans += inc();
        }
        return ans;
    }
};