#include <bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n, m;
vector <int> ls[N], topo;
int in[N], bio[N];
queue <int> Q;

void dfs(int node) {
    if (bio[node] == 1) {
        printf("-1\n");
        exit(0);
    }
    if (bio[node] == 2) return;
    bio[node] = 1;
    for (int x:ls[node]) dfs(x);
    bio[node] = 2;
}

void solve() {
    for (int i=1; i<=n; ++i) {
        if (!bio[i]) dfs(i);
        if (in[i] == 0) {
            Q.push(i);
        }
    }
    while (!Q.empty()) {
        int node = Q.front();
        Q.pop();
        topo.push_back(node);
        for (int sus:ls[node]) {
            in[sus]--;
            if (in[sus] == 0) Q.push(sus);
        }
    }
    printf("%d\n", (int)topo.size());
    for (int x:topo) printf("%d 0\n", x);
}

void load() {
    scanf("%d %d", &n, &m);
    for (int i=0; i<m; ++i) {
        int a, b;
        scanf("%d %d", &a, &b);
        ls[a].push_back(b);
        in[b]++;
    }
}

int main() {
    load();
    solve();
    return 0;
}
