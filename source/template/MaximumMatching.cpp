const int MAXN = 5e5 + 9;
int mx[MAXN], my[MAXN], dist[MAXN], vis[MAXN], cnt = 0;
vector<int> g[MAXN];
int n, m, L, R;
queue<int> q;

bool bfs(){
    FOR(i, 0, L - 1){
        if (mx[i] == -1){
            q.push(i);
            dist[i] = 0;
        }
        else dist[i] = -1;
    }

    bool f = false;

    while(!q.empty()){
        int u = q.front();
        q.pop();

        for(auto v: g[u]){
            if (my[v] == -1){
                f = true;
            }
            else if (dist[my[v]] == -1){
                dist[my[v]] = dist[u] + 1;
                q.push(my[v]);
            }
        }
    }
    return f;
}

bool dfs(int u){
    if (vis[u] == cnt) return false;
    vis[u] = cnt;
    for(auto v: g[u]){
        if (my[v] == -1){
            mx[u] = v;
            my[v] = u;
            return true;
        }
        else if (dist[my[v]] == dist[u] + 1 and dfs(my[v])){
            mx[u] = v;
            my[v] = u;
            return true;
        }
    }
    return false;
}

//Code for running
while(bfs()){
    ++cnt;
    FOR(i, 0, L - 1){
        if (mx[i] == -1) dfs(i);
    }
}