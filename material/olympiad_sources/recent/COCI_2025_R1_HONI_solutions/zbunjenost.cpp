#include<bits/stdc++.h>

#define pb push_back
#define x first
#define y second
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 2e5 + 5;
const int MOD = 1e9 + 7;

int add(int x, int y) {x += y;if(x >= MOD) x -= MOD;return x;}
int mult(ll x, ll y) {return x * y % MOD;}

int n, ans;
vector<ii> d;
int dp[maxn];
int out[maxn];
int nxt[maxn];
int lst[maxn];
vector<int> adj[maxn];

int cmp(ii a, ii b) {
	int l1 = min(a.y - a.x, n - a.y + a.x);
	int l2 = min(b.y - b.x, n - b.y + b.x);
	if(l1 != l2) return l1 < l2;
	return a < b;
}

int dfs(int p, int x) {
	dp[x] = 1;
	for(int y : adj[x])
		if(p != y) 
			dp[x] = mult(dp[x], add(dfs(x, y), 1));
	ans = add(ans, dp[x]);
	return dp[x];
}

int main() {
	scanf("%d", &n);
	for(int i = 3;i < n;i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		x--, y--;
		if(x > y) swap(x, y);
		d.pb({x, y});
	}

	sort(all(d), cmp);
	for(int i = 0;i < n;i++) {
		nxt[i] = (i + 1) % n;
		lst[i] = (i - 1 + n) % n;
	}

	int N = 0;
	vector<pair<ii, int>> M;
	for(auto [x, y] : d) {
		int z;
		if(nxt[nxt[x]] == y)
			z = nxt[x], nxt[x] = y, lst[y] = x;
		 else z = lst[x], lst[x] = y, nxt[y] = x;

		M.pb({{min(x, y), max(x, y)}, N});
		M.pb({{min(x, z), max(x, z)}, N});
		M.pb({{min(y, z), max(y, z)}, N});
		out[z] = 1, N++;
	}

	vector<int> t;
	for(int i = 0;i < n;i++)
		if(out[i] == 0) t.pb(i);
	for(int i : t)
		for(int j : t)
			if(i < j) M.pb({{i, j}, N});

	sort(all(M));
	for(int i = 1;i < (int)M.size();i++) {
		if(M[i].x == M[i - 1].x) {
			adj[M[i].y].pb(M[i - 1].y);
			adj[M[i - 1].y].pb(M[i].y);
		}
	}

	dfs(0, 0);
	printf("%d\n", ans);
	return 0;
}
