#include<bits/stdc++.h>

#define pb push_back
#define x first
#define y second
#define all(a) (a).begin(), (a).end()

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;

const int maxn = 2e5 + 5, off = (1 << 18);
const int MOD = 1e9 + 7;

int add(int x, int y) {x += y;if(x >= MOD) x -= MOD;return x;}
int mult(ll x, ll y) {return x * y % MOD;}
int pot(int n, int k) {
	if(k == 0) return 1;
	int ret = pot(n, k / 2);
	ret = mult(ret, ret);
	if(k & 1) ret = mult(ret, n);
	return ret;
}
int divide(int x, int y) {return mult(x, pot(y, MOD - 2));}

int n, q;
int deg[maxn];
int T[off << 1];
int fact[maxn];
int invf[maxn];
int inv[maxn];

void prep() {
	fact[0] = 1;
	for(int i = 1;i <= n;i++)
		fact[i] = mult(fact[i - 1], i);
	invf[n] = divide(1, fact[n]);
	for(int i = n - 1;i >= 0;i--)
		invf[i] = mult(invf[i + 1], i + 1);
	for(int i = 1;i <= n;i++) 
		inv[i] = mult(fact[i - 1], invf[i]);
	for(int i = 0;i < (off << 1);i++) T[i] = 1;
}

void add(int x, int lo, int hi, int a, int b, int v) {
	if(a > b) return;
	if(hi < a || b < lo) return;
	if(a <= lo && hi <= b) {
		T[x] = mult(T[x], v);
		return;
	}
	int mid = (lo + hi) / 2;
	add(x * 2, lo, mid, a, b, v);
	add(x * 2 + 1, mid + 1, hi, a, b, v);
}

int query(int x) {
	x += off;
	int ret = 1;
	while(x > 0)
		ret = mult(ret, T[x]), x >>= 1;
	return ret;
}

void add_diag(int x, int y) {
	deg[x]++, deg[y]++;
	if(x > y) swap(x, y);
	add(1, 0, off - 1, x + 1, y - 1, inv[n - (y - x) - 1]);
	add(1, 0, off - 1, 0, x - 1, inv[y - x - 1]);
	add(1, 0, off - 1, y + 1, n - 1, inv[y - x - 1]);
}

void rem_diag(int x, int y) {
	deg[x]--, deg[y]--;
	if(x > y) swap(x, y);
	add(1, 0, off - 1, x + 1, y - 1, n - (y - x) - 1);
	add(1, 0, off - 1, 0, x - 1, y - x - 1);
	add(1, 0, off - 1, y + 1, n - 1, y - x - 1);
}

int get(int x) {
	return mult(fact[n - 3 - deg[x]], query(x));
}

int main() {
	scanf("%d%d", &n, &q);
	prep();
	for(int i = 0;i < n - 3;i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		x--, y--;
		add_diag(x, y);
	}
	for(int i = 0;i < q;i++) {
		int t;
		scanf("%d", &t);
		if(t == 1) {
			int a, b, c, d;
			scanf("%d%d%d%d", &a, &b, &c, &d);
			a--, b--, c--, d--;
			rem_diag(a, b);
			add_diag(c, d);
		}
		if(t == 2) {
			int x;
			scanf("%d", &x);
			x--;
			printf("%d %d\n", n - 3 - deg[x], get(x));
		}
	}
	return 0;
}