#include <bits/stdc++.h>

using namespace std;

#define x first
#define y second
#define mp make_pair
#define pb push_back

typedef long long ll;

const ll MOD = 1e9+7;
const ll INF = 1e9+5;

const int MAXN = 5e3+5;

int n;
int a[MAXN];
int nex[MAXN][MAXN];
int memo[MAXN][MAXN];

int dp(int l, int r) {
	if (r > n) return -INF;
	if (r == n) return 1;
	if (memo[l][r] != -1) return memo[l][r];
	return memo[l][r] = max(dp(l, r+1), 1+dp(r+1, nex[l][r]));
}

int main() {
	memset(memo, -1, sizeof memo);
	scanf("%d", &n);
	for (int i=1 ; i<=n ; i++) {
		scanf("%d", a+i);
	}
	for (int r=0 ; r<=n ; r++) {
		ll suml = 0;
		ll sumr = 0;
		int ind = r;
		for (int l=r ; l>=0 ; l--) {
			suml += a[l];
			while (sumr < suml and ind<=n) {
				sumr += a[++ind];
			}
			nex[l][r] = ind;
		}
	}
	printf("%d\n", dp(1, 1));
	ll sum = 0;
	int l = 1;
	for (int i=1 ; i<=n ; i++) {
		sum += a[i];
		if (dp(l, i) == 1 + dp(i+1, nex[l][i])) {
			printf("%lld ", sum);
			int ll = l;
			l = i+1;
			i = nex[ll][i]-1;
			sum = 0;
			for (int j=l ; j<=i ; j++) sum += a[j];
		}
	}
	printf("%lld\n", sum);
	return 0;
}