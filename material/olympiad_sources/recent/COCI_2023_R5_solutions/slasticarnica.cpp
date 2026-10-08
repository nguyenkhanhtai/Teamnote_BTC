#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 5005, maxq = 2e5;

int dp[maxn][maxn][3];
int a[maxn];
int d[maxq], val[maxq];

int main() {
	int n, q;
	scanf("%d%d", &n, &q);
	for(int i = 0; i < n; i++) {
		scanf("%d", a + i);
	}
	for(int i = 0; i < q; i++) {
		scanf("%d%d", d + i, val + i);
	}
	dp[0][n][0] = dp[0][n][1] = dp[0][n][2] = 0;
	int lij, des, tren;
	for(int i = n - 1; i >= 0; i--) {
		for(int j = 0; j <= n - i; j++) {
			if(j && a[j - 1] >= val[dp[j - 1][j + i][0]]) {
				lij = dp[j - 1][j + i][1] + 1;
			}
			else {
				lij = 0;
			}
			if(j + i < n && a[j + i] >= val[dp[j][j + i + 1][0]]) {
				des = dp[j][j + i + 1][2] + 1;
			}
			else {
				des = 0;
			}
			if(!j) {
				tren = dp[j][j + i + 1][0];
				if(des == d[tren]) {
					tren++;
					des = 0;
				}
				dp[j][j + i][0] = tren;
				dp[j][j + i][1] = 0;
				dp[j][j + i][2] = des;
				continue;
			}
			tren = max(dp[j][j + i + 1][0], dp[j - 1][j + i][0]);
			if(tren != dp[j][j + i + 1][0]) {
				des = 0;
			}
			if(tren != dp[j - 1][j + i][0]) {
				lij = 0;
			}
			if(lij == d[tren] || des == d[tren]) {
				lij = 0;
				des = 0;
				tren++;
			}
			dp[j][j + i][0] = tren;
			dp[j][j + i][1] = lij;
			dp[j][j + i][2] = des;
		}
	}
	int sol = 0;
	for(int i = 0; i < n; i++) {
		sol = max(sol, dp[i][i][0]);
	}
	printf("%d\n", sol);
	return 0;
}
