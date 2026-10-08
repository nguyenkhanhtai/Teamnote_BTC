#include <iostream>

using namespace std;

int const MOD = 1e9 + 7;

using ll = long long;

ll add(ll a, ll b) {
  ll ret = (a + b) % MOD;
  if (ret < 0) ret += MOD;
  return ret;
}

ll mul(ll a, ll b) {
  ll ret = (a * b) % MOD;
  if (ret < 0) ret += MOD;
  return ret;
}

ll const half = (MOD + 1) / 2;

int const N = 5010;

ll fib[N];
ll numOfWays(int k) {
  if (k <= 1) return 0;
  
  return fib[k-1];
}

ll sumSingle(int k) {
  if (k <= 1) return 0;

  ll ret = add(mul(fib[k+1], fib[k+1]-1), -mul(fib[k], fib[k]-1));
  ret = mul(ret, half);

  return ret;
}

int n;
void precompute() {
  fib[1] = 1;
  for (int i = 2; i < N; ++i) {
    fib[i] = add(fib[i-1], fib[i-2]);
  }
}

ll dp[N];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  precompute();
  
  for (int i = 1; i <= n; ++i) {
    ll pot = 1;
    for (int k = i; k >= 2; --k) {
      dp[i] = add(dp[i], mul(numOfWays(k), dp[i-k]));
      dp[i] = add(dp[i], mul(sumSingle(k), pot));
      pot = mul(pot, 2);
    }
    cout << dp[i] << ' ';
  }
  cout << '\n';
  
  return 0;
}

