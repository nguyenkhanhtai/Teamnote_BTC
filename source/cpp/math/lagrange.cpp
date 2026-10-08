#pragma once
#include <bits/stdc++.h>
#include "rabin_miller.cpp"
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto y = lagrange(vector<int>{0,1,4},5,998244353);
  // y[i]=f(i), degree < y.size() < prime modulus; input values reduced.
  int lagrange(const vector<int>& y, int x, int p) {
    assert(x >= 0 && is_prime(p)&&!y.empty()&&(int)y.size()<p); int n=y.size(); x%=p;
    if (x < (int) n) return y[x] % p;
    vector<int> pre(n + 1, 1), suf(n + 1, 1), invfact(n, 1);
    for (int i = 0; i < n; ++i) pre[i + 1] = mul_mod(pre[i], x - i, p);
    for(int i=n-1; i>=0; --i)suf[i]=mul_mod(suf[i+1],x-i,p);
    int fact = 1;
    for (int i = 1; i < n; ++i) fact = mul_mod(fact, i, p);
    invfact[n - 1] = pow_mod(fact, p - 2, p);
    for(int i=n-1; i>0; --i)invfact[i-1]=mul_mod(invfact[i],i,p);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
      int term = mul_mod(y[i] % p, mul_mod(pre[i], suf[i + 1], p), p);
      term = mul_mod(term, mul_mod(invfact[i], invfact[n - 1 - i], p), p);
      if ((n - 1 - i) & 1) term = term ? p - term : 0;
      ans = static_cast<int>((__int128(ans) + term) % p);
    }
    return ans;
  }
//NOTEBOOK_END
}
