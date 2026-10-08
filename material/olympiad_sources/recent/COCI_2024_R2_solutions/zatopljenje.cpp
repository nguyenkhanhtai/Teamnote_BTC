#include<bits/stdc++.h>

#define pb push_back
#define x first
#define y second
#define all(a) (a).begin()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 2e5 + 5, off = (1 << 20);

int n, q;
int h[maxn];
int ans[maxn];
map<int, vector<int>> pos;
map<int, vector<pair<ii, int>>> qs;

struct SegTree {
	int in[maxn];
	int T[off << 1];
	void init() {
		memset(T, 0, sizeof T);
		memset(in, 0, sizeof in);
	}

	void update(int x, int v) {
		x += off;
		while(x > 0)
			T[x] += v, x >>= 1;
	}

	int query(int a, int b, int x = 1, int lo = 0, int hi = off - 1) {
		if(a > b) return 0;
		if(b < lo || hi < a) return 0;
		if(a <= lo && hi <= b) return T[x];
		int mid = (lo + hi) / 2;
		int L = query(a, b, x * 2, lo, mid);
		int R = query(a, b, x * 2 + 1, mid + 1, hi);
		return L + R;
	}

	void add(int x) {
		if(in[x - 1]) update(x - 1, -1);
		if(in[x + 1]) update(x, -1);
		in[x] = 1;
		if(!in[x - 1]) update(x - 1, 1);
		if(!in[x + 1]) update(x, 1);
	}

	int get(int l, int r) {return (query(l, r - 1) + in[l] + in[r]) / 2;}
} S;

int main() {
	S.init();
	scanf("%d%d", &n, &q);
	set<int> vals;
	for(int i = 1;i <= n;i++) {
		scanf("%d", h + i);
		pos[-h[i]].pb(i);
		vals.insert(-h[i]);
	}
	for(int i = 0;i < q;i++) {
		int l, r, x;
		scanf("%d%d%d", &l, &r, &x);
		vals.insert(-x);
		qs[-x].pb({{l, r}, i});
	}

	for(int x : vals) {
		for(auto qi : qs[x])
			ans[qi.y] = S.get(qi.x.x, qi.x.y);
		for(int i : pos[x]) S.add(i);
	}
	for(int i = 0;i < q;i++)
		printf("%d\n", ans[i]);
	return 0;
}
