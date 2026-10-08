#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;

const int maxn = 1e5 + 5, Log = 18, pot = (1 << Log), maxm = 8e6;
const ll inf = 1e18;

struct node {
	__int128 val;
	node *l, *d;
};

node cvorovi[maxm];
node *root[maxn * 2];
int curr;

ll getval(node *p) {
	if(p == nullptr) {
		return 0;
	}
	return p -> val;
}

node* update(int L, int D, node *p, int &l, int &d, ll &val) {
	if(p != nullptr) {
		cvorovi[curr] = *p;
	}
	p = &cvorovi[curr++];
	if(L >= l && D <= d) {
		p -> val += val;
		return p;
	}
	if((L + D) / 2 >= l) {
		p->l = update(L, (L + D) / 2, p -> l, l, d, val);
	}
	if((L + D) / 2 + 1 <= d){
		p->d = update((L + D) / 2 + 1, D, p -> d, l, d, val);
	}
	return p;
}

__int128 query(int L, int D, node *p, int &x) {
	if(p == nullptr) {
		return 0;
	}
	if(L == x && D == x) {
		return p -> val;
	}
	if((L + D) / 2 >= x) {
		return query(L, (L + D) / 2, p -> l, x) + p -> val;
	}
	else {
		return query((L + D) / 2 + 1, D, p -> d, x) + p -> val;
	}
}

int n;
vector < pair < int, int > > ms[maxn];
int parent[maxn][Log];
int dep[maxn];

void precompute() {
	for(int i = 1; i < Log; i++) {
		for(int j = 0; j < n; j++) {
			parent[j][i] = parent[parent[j][i - 1]][i - 1];
		}
	}
}

void digni(int &x, int &y) {
	int raz = dep[x] - dep[y];
	for(int i = 0; i < Log; i++) {
		if((1 << i) & raz) {
			x = parent[x][i];
		}
	}
}

int lca(int x, int y) {
	if(dep[x] < dep[y]) {
		swap(x, y);
	}
	digni(x, y);
	if(x == y) {
		return x;
	}
	for(int i = Log - 1; i >= 0; i--) {
		if(parent[x][i] != parent[y][i]) {
			x = parent[x][i];
			y = parent[y][i];
		}
	}
	return parent[x][0];
}

int rev[maxn];
pair < int, int > interval[maxn];
int tren;

int v[maxn], c[maxn], o[maxn];
int pos[maxn];

bool cmp(int x, int y) {
	return v[x] < v[y];
}

void dfs(int x, int prosl, int d) {
	parent[x][0] = prosl;
	dep[x] = d;
	interval[x].first = tren++;
	for(int i = 0; i < (int) ms[x].size(); i++) {
		if(ms[x][i].first != prosl) {
			rev[ms[x][i].second] = ms[x][i].first;
			dfs(ms[x][i].first, x, d + 1);
		}
	}
	interval[x].second = tren - 1;
}


int binary(int x, int y, ll val) {
	int z = lca(x, y);
	int lo = 0, hi = n * 2 - 3, mid;
	while(lo < hi) {
		mid = (lo + hi) / 2;
		if(query(0, pot - 1, root[mid], interval[x].first) + query(0, pot - 1, root[mid], interval[y].first) - query(0, pot - 1, root[mid], interval[z].first) * 2 <= val) {
			lo = mid + 1;
		}
		else {
			hi = mid;
		}
	}
	return lo - 1;
}

vector < pair < int, pair < int, ll > > > event;

int main() {
	scanf("%d", &n);
	int a, b;
	pair < int, ll > p;
	for(int i = 0; i < n - 1; i++) {
		scanf("%d%d%d%d%d", &a, &b, v+i, c+i, o+i);
		a--;
		b--;
		ms[a].push_back({b, i});
		ms[b].push_back({a, i});
		event.push_back({v[i], {i, c[i]}});
		event.push_back({o[i], {i, inf}});
	}
	dfs(0, 0, 0);
	precompute();
	sort(event.begin(), event.end());
	ll vv;
	for(int i = 0; i < n * 2 - 2; i++) {
		a = rev[event[i].second.first];
		vv = event[i].second.second;
		root[i + 1] = update(0, pot - 1, root[i], interval[a].first, interval[a].second, vv);
	}
	int q;
	scanf("%d", &q);
	ll x;
	for(int i = 0; i < q; i++) {
		scanf("%d%d%lld", &a, &b, &x);
		a--;
		b--;
		printf("%d\n", event[binary(a, b, x)].first);
	}
	return 0;
}
