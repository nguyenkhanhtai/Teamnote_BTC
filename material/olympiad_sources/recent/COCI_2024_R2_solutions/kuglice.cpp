#include <bits/stdc++.h>
#define X first
#define Y second

using namespace std;
typedef long long llint;

const int maxn = 5010;
const int base = 31337;
const int mod = 1e9+7;
const int inf = 0x3f3f3f3f;
const int logo = 20;
const int off = 1 << logo;
const int treesiz = off << 1;

int n;
int niz[maxn];
int mini[maxn], maxi[maxn];
int dp[maxn][maxn];

inline bool check(int l, int r, int x) {
	return maxi[x] <= r && mini[x] >= l; 
}

int f(int l, int r) {
	if (l > r) return 0;

	int &ret = dp[l][r];
	if (ret != -maxn) return ret;

	return ret = max(check(l, r, niz[r]) - f(l, r - 1), check(l, r, niz[l]) - f(l + 1, r));
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", niz+i);

	memset(mini, inf, sizeof mini);
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		if (mini[niz[i]] == inf) 
			cnt++, mini[niz[i]] = i;
		maxi[niz[i]] = i;
	}

	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++)
			dp[i][j] = -maxn;

	int diff = f(0, n - 1);
	int a = (cnt + diff) / 2;
	int b = cnt - a;

	printf("%d:%d\n", a, b);
	return 0;
}
