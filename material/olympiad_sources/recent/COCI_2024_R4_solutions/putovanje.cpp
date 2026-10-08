#include <bits/stdc++.h>
using namespace std;

const int N = 5e4 + 2;

int n, m, d[N], dist[N], uk;
bool bio[N], ok = 1;

vector<int> adj[N], v[N];
queue<int> bfs;
bitset<N> source[N];

void flood_fill() {

	while (!bfs.empty()) {
		int node = bfs.front();
		bfs.pop();

		if (!dist[node]) continue;

		while (!v[dist[node] - 1].empty()) {
			int x = v[dist[node] - 1].back();
			v[dist[node] - 1].pop_back();

			if (bio[x]) {
				if (dist[x] != d[x]) ok = 0;
				continue;
			}

			bio[x] = 1;
			dist[x] = d[x];
			bfs.push(x);
			source[x].set(x);
		}

		for (int x : adj[node]) {
			if (dist[x] < dist[node]) {
				dist[x] = dist[node] - 1;
				source[x] |= source[node];
				if (!bio[x]) bfs.push(x);
				bio[x] = 1;
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(0);

	cin >> n >> m;

	for (int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v, --u, --v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	for (int i = 0; i < n; ++i) {
		cin >> d[i];
		if (d[i] != -1) {
			v[d[i]].push_back(i);
			++uk;
		}
	}

	int j = n - 1;
	while (j >= 0 && v[j].empty()) --j;

	if (j == -1) {
		cout << n << "\n";
		for (int i = 1; i <= n; ++i) cout << i << " ";
		return 0;
	}

	for (int i : v[j]) {
		dist[i] = j;
		bio[i] = 1;
		source[i].set(i);
		bfs.push(i);
	}
	flood_fill();

	vector<int> ans;

	for (int i = 0; i < n; ++i) {
		if (ok && !dist[i] && source[i].count() == uk) {
			ans.push_back(i);
		}
	}

	cout << ans.size() << "\n";
	for (int x : ans) cout << x + 1 << " ";
	return 0;
}
