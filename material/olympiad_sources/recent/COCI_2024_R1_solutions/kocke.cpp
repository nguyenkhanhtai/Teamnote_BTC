#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9 + 7;
const int MAXN = 5005;

inline int add(int a, int b){
	return (a + b >= MOD) ? a + b - MOD : a + b;
}
inline int mul(int a, int b){
	return (long long) a * b % MOD;
}

int n, k, ans, dp[MAXN][MAXN], suf[MAXN];

int main(){
	cin >> n >> k;

	dp[2][n - 1] = 2;

	for(int i = 3; i <= n; ++i){
		suf[n - 1] = dp[i - 1][n - 1];
		for(int j = n - 2; j > 0; --j){
			suf[j] = add(dp[i - 1][j], suf[j + 2]);
		}

		for(int j = n - 2; j > 0; --j){
			dp[i][j] = suf[j + 1];
			if(i + j <= n) dp[i][j] = add(dp[i][j], suf[i + j - 1]);
		}
	}

	for(int i = 2; i <= min(n, k); ++i){
		for(int j = 1; j < n; ++j){
			ans = add(ans, mul(dp[i][j], k - i + 1));
		}
	}

	cout << ans << "\n";

	return 0;
}
