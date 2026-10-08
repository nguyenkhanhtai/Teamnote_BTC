#include<bits/stdc++.h>

using namespace std;

typedef long long llint;
typedef pair <int, int> pi;

const int MAXN = 100005;
const int INF = 1000000007;

int n, root, special;
int head[MAXN], par[MAXN];
int dp[MAXN][2][2][2][2];
vector <int> v[MAXN];

int nadi (int x) {
    if (x == head[x]) return x;
    return head[x] = nadi(head[x]);
}

void dfs (int x, int rod) {
    par[x] = rod;
    for (auto sus : v[x]) {
        if (sus == rod) continue;
        dfs(sus, x);
    }
}

int calc (int x, int me, int up, int rt, int sp) {
    if (dp[x][me][up][rt][sp] != -1) return dp[x][me][up][rt][sp];

    llint res = INF;

    bool ok = 1;
    if (x == root && me != rt) ok = 0;
    if (x == special && me != sp) ok = 0;
    if (x == special && up && rt) ok = 0;
    if (!ok) return dp[x][me][up][rt][sp] = INF;

    bool covered = 0;
    if (up) covered = 1;
    if (x == root && sp) covered = 1;
    if (x == special && rt) covered = 1;

    llint sum = me;
    for (auto sus : v[x]) {
        if (sus == par[x]) continue;
        sum += calc(sus, 0, me, rt, sp);
    }

    if (covered) {
        res = min(res, sum);
    } else {
        for (auto sus : v[x]) {
            if (sus == par[x]) continue;
            llint val = sum - calc(sus, 0, me, rt, sp) + calc(sus, 1, me, rt, sp);
            res = min(res, val);
        }
    }

    return dp[x][me][up][rt][sp] = res;
}

void solve () {
    int sol = INF;
    for (int rt = 0; rt <= 1; rt++) {
        for (int sp = 0; sp <= 1; sp++) {
            sol = min(sol, calc(root, rt, 0, rt, sp));
        }
    }
    if (sol == INF) cout << -1; else cout << sol;
}

int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    memset(dp, -1, sizeof dp);
    cin >> n;
    for (int i = 1; i <= n; i++) {
        head[i] = i;
    }
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        int pa = nadi(a);
        int pb = nadi(b);
        if (pa == pb) {
            root = a;
            special = b;
        } else {
            head[pa] = pb;
            v[a].push_back(b);
            v[b].push_back(a);
        }
    }
    dfs(root, 0);
    solve();
    return 0;
}
