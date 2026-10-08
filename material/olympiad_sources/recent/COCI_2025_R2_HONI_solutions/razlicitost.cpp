#include <bits/stdc++.h>
#define X first
#define Y second

using namespace std;
typedef long long llint;

const int maxn = 2e5+10;
const int base = 31337;
const int mod = 1e9+7;
const int inf = 0x3f3f3f3f;
const int logo = 20;
const int off = 1 << logo;
const int treesiz = off << 1;

int add(int a, int b) {
	int out = a + b;
	if (out >= mod) out -= mod;
	return out;
}

int mul(int a, int b) {
	llint out = (llint)a * b;
	out %= mod;
	return out;
}

int n, m, gc;
llint k;
llint a[maxn], b[maxn];
vector< int > v[maxn];
int p[maxn];

int solve(vector< int > a, vector< int > b) {
	for (int i = 0; i < gc; i++) {
		v[i].clear();
		v[i].push_back(0);
	}

	int t = m / gc;
	for (int i = 0; i < gc; i++) {
		int ptr = i;
		for (int j = 0; j < m / gc; j++) {
			p[ptr] = j + 1;
			v[i].push_back(b[ptr]);
			ptr += n; ptr %= m;
		}
		for (int j = 0; j < m / gc; j++)
			v[i].push_back(v[i][1 + j]);
		for (int j = 1; j < v[i].size(); j++) v[i][j] += v[i][j - 1];
	}

	int out = 0;
	for (int i = 0; i < n; i++) {
		if (i > k) break;

		int ac = p[i % m];
		llint c = (k - i) / ((llint)n * m / gc); c %= mod;
		llint rem = (k - i) % ((llint)n * m / gc);
		rem = (rem + n - 1) / n;
		int sum = v[i % gc][t];

		if (a[i] == 0) {
			out = add(out, mul(c, sum));
			out = add(out, v[i % gc][ac + rem - 1] - v[i % gc][ac - 1]);
		} else {
			out = add(out, mul(c, t - sum));
			out = add(out, rem - v[i % gc][ac + rem - 1] + v[i % gc][ac - 1]);
		}
	}

	return out;
}

int main() {
	scanf("%d%d%lld", &n, &m, &k);
	for (int i = 0; i < n; i++)
		scanf("%lld", a+i);
	for (int i = 0; i < m; i++)
		scanf("%lld", b+i);
	gc = __gcd(n, m);

	int out = 0;
	int pot = 1;
	for (int k = 0; k < 62; k++) {
		vector< int > ra(n), rb(m);
		for (int i = 0; i < n; i++) ra[i] = (a[i] >> k) & 1LL;
		for (int i = 0; i < m; i++) rb[i] = (b[i] >> k) & 1LL;

		out = add(out, mul(solve(ra, rb), pot));
		pot = add(pot, pot);
	}
	printf("%d\n", out);
	return 0;
}