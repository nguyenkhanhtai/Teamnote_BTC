#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int const MOD = 1e9 + 7;

inline int add(int a, int b) {
  int ret = (a + b) % MOD;
  if (ret < 0) ret += MOD;
  return ret;
}

inline int mul(int a, int b) {
  int ret = ((long long)a * b) % MOD;
  if (ret < 0) ret += MOD;
  return ret;
}

inline int pot(int n, int k) {
  int ret = 1;
  while (k) {
    if (k & 1) {
      ret = mul(ret, n);
    }
    n = mul(n, n);
    k >>= 1;
  }
  return ret;
}

inline int dv(int a, int b) {
  return mul(a, pot(b, MOD - 2));
}



int n;
vector<int> value;
vector<vector<pair<int, int>>> child;
vector<int> down, up, ans;

int const half = dv(1, 2);

int const N = 1e6 + 10;
int fact[N], invFact[N];
int memo[N];

inline int nCr(int n, int r) {
  if (r < 0 || r > n) return 0;
  return mul(fact[n], mul(invFact[r], invFact[n-r]));
}

inline int getProb(int k) {
  if (memo[k] != -1) return memo[k];
  
  memo[k] = 0;
  for (int i = 0; i < k; ++i) {
    memo[k] = add(memo[k], dv(nCr(k-1, i), i+1));
  }
  memo[k] = dv(memo[k], pot(2, k));
  return memo[k];
}

void rec1(int v) {
  down[v] = value[v];
  for (auto &[u, prob] : child[v]) {
    rec1(u); 
    prob = getProb(size(child[v]));
    down[v] = add(down[v], mul(prob, down[u]));
  }
}

void tmpRerooter(int v, int p, int upper = 0) {
  int k = (int)size(child[v]) + (p != -1);
  int lg = 0;
  while ((1 << lg) <= k) lg++;
  lg--;
  vector<int> vals(k);
  vector<int> excsum(k);
  if (p != -1) vals.back() = upper;
  for (int i = 0; i < (int)size(child[v]); ++i) {
    vals[i] = down[child[v][i].first];
  }
  for (int bit = lg; bit >= 0; --bit) {
    for (int i = k - 1; i >= 0; --i) excsum[i] = excsum[i/2];
    int sz = k - (k & !bit);
    for (int i = 0; i < sz; ++i) {
      int ind = (i >> bit) ^ 1;
      excsum[ind] = add(excsum[ind], vals[i]);
    }
  }
  for (auto const &a : vals) ans[v] = add(ans[v], a);
  ans[v] = add(value[v], mul(getProb(k), ans[v]));
  vals.clear();
  int np = getProb((int)size(child[v]) - 1 + (p != -1));
  for (int i = 0; i < (int)size(child[v]); ++i) {
    tmpRerooter(child[v][i].first, v, add(value[v], mul(np, excsum[i])));
  }
}

void solve() {
  cin >> n;
  fact[0] = invFact[0] = 1;
  for (int i = 1; i <= n; ++i) {
    fact[i] = mul(fact[i-1], i);
    invFact[i] = dv(invFact[i-1], i);
  }
  value.resize(n);
  child.resize(n);
  down.resize(n);
  up.resize(n);
  ans.resize(n);
  for (int i = 1; i < n; ++i) {
    int p;
    cin >> p;
    p--;
    child[p].emplace_back(i, 0);
  }
  for (auto &it : value) cin >> it;
  rec1(0);
  tmpRerooter(0, -1);
  for (auto a : ans) cout << a << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);


  memset(memo, -1, sizeof memo);
  solve(); 

  return 0;
}

