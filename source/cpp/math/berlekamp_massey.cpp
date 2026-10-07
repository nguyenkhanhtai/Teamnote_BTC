#pragma once
#include <bits/stdc++.h>
#include "ntt.cpp"
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  // Prime modulus 998244353; s[i]=sum recurrence[j]*s[i-1-j].
  vector<int> berlekamp_massey(vector<int> s) {
    for (auto& x : s) x = (x % MOD + MOD) % MOD;
    vector<int> C {1}, B {1}; int L = 0, gap = 1; long long previous = 1;
    for (int i = 0; i < (int) s.size(); ++i) {
      long long d = (s[i] % MOD + MOD) % MOD;
      for (int j = 1; j <= L; ++j) d = (d + 1LL * C[j] * s[i - j]) % MOD;
      if (!d) { ++gap; continue; }
      auto old = C; long long coef = d * power(previous, MOD - 2) % MOD;
      if (C.size() < B.size() + gap) C.resize(B.size() + gap);
      for(int j=0;j<(int)B.size();++j)C[j+gap]=(C[j+gap]-coef*B[j]%MOD+MOD)%MOD;
      if(2*L<=i){ L=i+1-L; B=move(old); previous=d; gap=1; } else ++gap;
    }
    C.resize(L + 1); C.erase(C.begin());
    for (auto& x : C) x = (MOD - x) % MOD;
    return C;
  }
  int recurrence_term(const vector<int>&initial,const vector<int>&recurrence,uint64_t k){
    int n = recurrence.size();
    if (k < initial.size()) return(initial[k] % MOD + MOD) % MOD;
    if (!n) return 0;
    assert(initial.size() >= (size_t) n);
    auto combine = [&](const vector<int>& a, const vector<int>& b) {
      vector<int> c(2 * n - 1);
      for(int i=0;i<n;++i)for(int j=0;j<n;++j)c[i+j]=(c[i+j]+1LL*a[i]*b[j])%MOD;
      for(int i=2*n-2;i>=n;--i)for(int j=1;j<=n;++j)c[i-j]=(c[i-j]+1LL*c[i]*recurrence[j-1])%MOD;
      c.resize(n); return c;
    }; vector<int> a(n), x(n); a[0] = 1;
    if (n == 1) x[0] = recurrence[0];
    else x[1] = 1;
    for (; k; k >>= 1, x = combine(x, x)) if (k & 1) a = combine(a, x);
    long long ans = 0;
    for(int i=0; i<n; ++i)ans=(ans+1LL*a[i]*initial[i])%MOD;
    return(ans + MOD) % MOD;
  }
//NOTEBOOK_END
}
