#pragma once
#include <bits/stdc++.h>
#include "rabin_miller.cpp"
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  // y[i]=f(i), degree < y.size() < prime modulus; input values reduced.
  U64 lagrange(const vector<U64>& y, U64 x, U64 p) {
    assert(is_prime(p)&&!y.empty()&&y.size()<p); int n=y.size(); x%=p;
    if (x < (U64) n) return y[x] % p;
    vector<U64> pre(n + 1, 1), suf(n + 1, 1), invfact(n, 1);
    for (int i = 0; i < n; ++i) pre[i + 1] = mul_mod(pre[i], x - i, p);
    for(int i=n-1; i>=0; --i)suf[i]=mul_mod(suf[i+1],x-i,p);
    U64 fact = 1;
    for (int i = 1; i < n; ++i) fact = mul_mod(fact, i, p);
    invfact[n - 1] = pow_mod(fact, p - 2, p);
    for(int i=n-1; i>0; --i)invfact[i-1]=mul_mod(invfact[i],i,p);
    U64 ans = 0;
    for (int i = 0; i < n; ++i) {
      U64 term = mul_mod(y[i] % p, mul_mod(pre[i], suf[i + 1], p), p);
      term = mul_mod(term, mul_mod(invfact[i], invfact[n - 1 - i], p), p);
      if ((n - 1 - i) & 1) term = term ? p - term : 0;
      ans = U64((U128(ans) + term) % p);
    }
    return ans;
  }
//NOTEBOOK_END
}
