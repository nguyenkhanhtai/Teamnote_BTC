#include <iostream>
#include <vector>

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
vector<vector<int>> child;
vector<int> down, up, ans;

int const half = dv(1, 2);

inline int getProb(int k) {
  return dv(add(1, -pot(half, k)), k);
}

void rec1(int v) {
  down[v] = 0;
  int prob = getProb(size(child[v]));
  for (auto u : child[v]) {
    rec1(u); 
    down[v] = add(down[v], mul(prob, add(value[u], down[u])));
  }
}

void rec2(int v, int p) {
  if (p != -1) {
    int probp = getProb(size(child[p]));
    if (p == 0) {
      int probpa = getProb((int)size(child[p]) - 1);
      up[v] = add(value[p], mul(dv(probpa, probp), add(down[p], -mul(probp, add(value[v], down[v])))));
    } else {
      up[v] = add(value[p], add(down[p], mul(probp, add(up[p], -add(value[v], down[v])))));
    }
    int pprob = getProb(size(child[v]));
    int nprob = getProb(size(child[v]) + 1);
    ans[v] = add(value[v], add(mul(nprob, up[v]), mul(dv(nprob, pprob), down[v])));
  } else {
    ans[v] = add(value[v], down[v]);
  }
  for (auto u : child[v]) {
    rec2(u, v);
  }
}

void solve() {
  cin >> n;
  value.resize(n);
  child.resize(n);
  down.resize(n);
  up.resize(n);
  ans.resize(n);
  for (int i = 1; i < n; ++i) {
    int p;
    cin >> p;
    p--;
    child[p].push_back(i);
  }
  for (auto &it : value) cin >> it;
  rec1(0);
  rec2(0, -1);
  for (auto a : ans) cout << a << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  solve(); 

  return 0;
}

