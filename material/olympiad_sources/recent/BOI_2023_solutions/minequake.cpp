/*
 * O(n) solution with O(1) stack space
 *
 */ 
#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;


int n;
vector<vector<int> > g;
vector<int> pp;
vector<ll> up, ans;
vector<int> siz;
vector<int> ord;

void dfs(int u, int p = -1){
    for(auto &e : g[u]) if(e != p){
        pp[e] = u;
        dfs(e, u);
    }
    ord.push_back(u);
}

auto pass = [](auto&&args...) {};

signed main(){
    int n;
    cin >> n;
    ans.assign(n, -1);
    up.assign(n, 0);
    siz.assign(n, 1);
    pp.assign(n, -1);
    g.assign(n, {});
    for(int i=1; i<n; ++i){
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(0);
    ord.pop_back(); // remove root
    for(int u : ord){
        const int p = pp[u];
        up[p] += siz[u] * (ll)(2*siz[p] - 1);
        up[p] += up[u];
        siz[p] += siz[u];
    }
    ans[0] = up[0];
    reverse(ord.begin(), ord.end());
    for(int u : ord){
        const int p = pp[u];
        ans[u] = ans[p] - (n-siz[u]) + siz[u];
    }
    auto ret = *min_element(ans.begin(), ans.end());
    cout << ret << "\n";
}

