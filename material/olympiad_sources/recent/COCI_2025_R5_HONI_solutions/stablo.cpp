#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

const int N = 1e6 + 2;

int n, k, ans[N], U[N], V[N];
vector<pii> adj[N];

int edge[N], dep[N], par[N];
int uf[N], sz[N], label[N];

void dfs(int node, int anc) {
	par[node] = anc;
	dep[node] = dep[anc] + 1;
	for (pii p : adj[node]) {
		if (p.first == anc) continue;
		edge[p.first] = p.second;
		dfs(p.first, node);
	}
}

int f(int node) {
	if (uf[node] == -1) return node;
	return uf[node] = f(uf[node]);
}

int join(int u, int v) {
	u = f(u); v = f(v);
	if (u == v) return label[u];
	if (sz[u] < sz[v]) swap(u, v);

	sz[u] += sz[v];
	uf[v] = u;
	if (dep[label[u]] > dep[label[v]]) label[u] = label[v];

	return label[u];
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> n >> k;

	for (int i = 1; i < n; ++i) {
		int u, v; cin >> u >> v;
		--u, --v;
		adj[u].push_back({v, i});
		adj[v].push_back({u, i});
	}

	dfs(0, 0);
	for (int i = 0; i < n; ++i) {
		uf[i] = -1;
		sz[i] = 1;
		label[i] = i;
	}

	for (int i = 0; i < k; ++i) {
		cin >> U[i] >> V[i], --U[i], --V[i];
	}

	for (int i = k - 1; i >= 0; --i) {
		U[i] = label[f(U[i])];
		V[i] = label[f(V[i])];

		while (U[i] != V[i]) {
			if (dep[U[i]] < dep[V[i]]) swap(U[i], V[i]);
			ans[edge[U[i]]] = i + 1;
			U[i] = join(U[i], par[U[i]]);
		}
	}

	for (int i = 1; i < n; ++i) cout << ans[i] << " ";
	cout << "\n";

	return 0;
}
