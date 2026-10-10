#pragma once
#include <bits/stdc++.h>
#include "rabin_miller.cpp"
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: vector<int> a(8,1); fwht(a,Walsh::Xor,998244353);
  enum class Walsh {Xor, And, Or};
  // mod must be prime; inverse XOR requires an odd mod.
  void fwht(vector<int>& a, Walsh kind, int mod, bool inverse = false) {
    int n = a.size(); assert(n && !(n & (n - 1)) && mod > 1);
    assert(!inverse || kind != Walsh::Xor || (mod & 1));
    for (int& x : a) { x %= mod; if (x < 0) x += mod; }
    for (int len = 1; len < n; len <<= 1)
      for (int i = 0; i < n; i += 2 * len)
        for (int j = 0; j < len; ++j) {
          int& x = a[i + j]; int& y = a[i + j + len];
          int u = x, v = y;
          if (kind == Walsh::Xor) {
            x = (int)(((__int128)u + v) % mod);
            y = u >= v ? u - v : mod - (v - u);
          } else if (kind == Walsh::Or) {
            y = inverse ? (v >= u ? v - u : mod - (u - v))
                        : (int)(((__int128)u + v) % mod);
          } else {
            x = inverse ? (u >= v ? u - v : mod - (v - u))
                        : (int)(((__int128)u + v) % mod);
          }
        }
    if (inverse && kind == Walsh::Xor) {
      int inv_n = pow_mod(n % mod, mod - 2, mod);
      for (int& x : a) x = mul_mod(x, inv_n, mod);
    }
  }
//NOTEBOOK_END
}
