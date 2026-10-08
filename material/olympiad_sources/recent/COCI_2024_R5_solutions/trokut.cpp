#include <bits/stdc++.h>
#define X first
#define Y second

using namespace std;
typedef long long llint;

const int maxn = 200;
const int base = 31337;
const int mod = 1e9+7;
const int inf = 0x3f3f3f3f;
const int logo = 20;
const int off = 1 << logo;
const int treesiz = off << 1;

const int period = 34;

int t;
int dp[maxn + 10];

int main() {
	for (int i = 2; i <= maxn; i++) {
		vector< int > v;
		for (int j = 0; j <= i - 2; j++)
			v.push_back(dp[j] ^ dp[i - 2 - j]);
		sort(v.begin(), v.end());
		v.resize(unique(v.begin(), v.end()) - v.begin());

		int mx = 0;
		while (mx < v.size() && v[mx] == mx) mx++;
		dp[i] = mx;
	}

	scanf("%d", &t);
	while (t--) {
		int n;
		scanf("%d", &n);

		if (n > maxn) {
			n %= period;
			n += 4 * period;
		}

		if (dp[n]) printf("Lucija\n");
		else printf("Ivan\n");
	}
	return 0;
}