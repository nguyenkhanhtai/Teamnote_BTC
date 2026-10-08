#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

const int maxn = 5005;

ll dp[maxn][2][maxn];
int p[maxn], t[maxn], o[maxn];

int main() {
  int n, d;
  scanf("%d%d", &n, &d);
  for(int i = 0; i < n; i++) {
    scanf("%d%d%d", p + i, t + i, o + i);
  }
  for(int i = 0; i < n; i++) {
    for(int j = 1; j <= d; j++) {
      dp[i + 1][0][j] = max({dp[i][0][j], dp[i][1][j], dp[i + 1][0][j - 1]});
      if(j >= p[i]) {
        dp[i + 1][1][j] = dp[i + 1][0][j - p[i]];
      }
      if(j >= p[i] + t[i]) {
        dp[i + 1][1][j] = max(dp[i + 1][1][j], dp[i + 1][1][j - t[i]] + o[i]);
      }
    }
  }
  printf("%lld\n", max(dp[n][0][d], dp[n][1][d]));
  return 0;
}

