#include<bits/stdc++.h>

using namespace std;

const int MAXN = 5e5 + 5;

int n, m;
int dp[2 * MAXN];
int nxt[2 * MAXN];
int deg[2 * MAXN];
int side[2 * MAXN];
int match[2 * MAXN];
vector<int> adj[2 * MAXN];

void dfs(int u, int flag) {
    if(side[u] != -1) return;
    side[u] = flag;
    for(int v : adj[u]) dfs(v, !flag);
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for(int i = 0, u, v;i < m;i++) {
        cin >> u >> v;
        u--, v--;
        deg[u]++, deg[v]++;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    memset(side, -1, sizeof side);
    for(int i = 0;i < 2 * n;i++) 
        if(side[i] == -1) dfs(i, 0);
    
    queue<int> q;
    for(int i = 0;i < 2 * n;i++)
        if(!side[i] && deg[i] == 1) q.push(i);
    
    memset(nxt, -1, sizeof match);
    memset(match, -1, sizeof match);
    int ans = -1, s = -1;
    while(q.size()) {
        int u = q.front();
        q.pop();
        for(int v : adj[u])
            if(match[v] == -1)
                match[v] = u, match[u] = v;
        
        for(int v : adj[match[u]]) {
            if(match[v] == -1) {
                if(dp[v] < dp[u] + 1)
                    dp[v] = dp[u] + 1, nxt[v] = u;
                deg[v]--;
                if(deg[v] == 1) q.push(v);
            }
        }

        if(dp[u] > ans) ans = dp[u], s = u;
    }

    cout << 2 * (ans + 1) << "\n";
    while(true) {
        cout << match[s] + 1 << " " << s + 1;
        s = nxt[s];
        if(s == -1) break;
        else cout << " ";
    }
    cout << "\n";
    return 0;
}