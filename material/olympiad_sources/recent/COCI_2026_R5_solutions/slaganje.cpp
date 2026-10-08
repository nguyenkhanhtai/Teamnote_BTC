#include<bits/stdc++.h>

#define pb push_back
#define x first
#define y second
#define all(a) (a).begin(), (a).end()

using namespace std;

const int MAXN = 2005;

int n;
int par[MAXN];
int ans[MAXN];
int dep[MAXN];
int used[MAXN];
vector<int> adj[MAXN];
vector<int> star[MAXN];

int cmp(int x, int y) {
    if(dep[x] != dep[y])
        return dep[x] > dep[y];
    return x < y;
}

int add(int x, int y) {return (x + y + n) % n;}

void dfs(int p, int u) {
    par[u] = p;
    if(p != -1) dep[u] = dep[p] + 1;
    for(int v : adj[u])
        if(v != p) dfs(u, v);
}

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for(int i = 1, u, v;i < n;i++) {
        cin >> u >> v, u--, v--;
        adj[u].pb(v), adj[v].pb(u);
    }

    dfs(-1, 0);
    vector<int> ord(n);
    iota(all(ord), 0);
    sort(all(ord), cmp);
    int center = -1;
    for(int x : ord) {
        if(!star[x].size() && x > 0) star[par[x]].pb(x);
        if(star[x].size() && star[x].size() > 1) center = x;
    }
    if(center == -1) {
        for(int x : ord) {
            if(star[x].size()) {
                center = x;
                int y = par[x];
                star[x].pb(y);
                if(star[y].size()) star[y].clear();
                else if(y && star[par[y]].size()) star[par[y]].clear();
                break;
            }
        }
    }  
    
    vector<int> stars = {center};
    int sum = star[center].size();
    while(sum > (n / 2))
        sum--, star[center].pop_back();
    for(int x : ord) {
        if(sum == (n / 2)) break;
        if(x != center && star[x].size()) {
            stars.pb(x);
            sum += star[x].size();
            while(sum > (n / 2))
                sum--, star[x].pop_back();
        }
    }

    vector<int> l = {0, 0};
    vector<int> r = {n / 2, (n + 1) / 2};
    vector<int> off = {-1, 1};
    int f = 0;
    memset(ans, -1, sizeof ans);
    for(int c : stars) {
        ans[l[f]] = c, used[c] = 1;
        for(int u : star[c]) {
            ans[r[f]] = u, used[u] = 1;
            r[0] = add(r[0], off[0]);
            r[1] = add(r[1], off[1]);
        }
        f = !f;
        l[f] = add(l[f], off[!f]);
        r[f] = add(r[f], off[!f]);
    }

    for(int i = 0;i < n;i++) {
        if(ans[i] != -1) continue;
        for(int j = 0;j < n;j++)
            if(used[j] == 0) {
                ans[i] = j, used[j] = 1;
                break;
            }
    }

    for(int i = 0;i < n;i++)
        for(int j = 0;j < n;j++)
            cout << ans[(i + j) % n] + 1 << " \n"[j + 1 == n];
    return 0;
}