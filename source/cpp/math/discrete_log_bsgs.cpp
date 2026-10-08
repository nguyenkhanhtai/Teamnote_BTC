#pragma once
#include <bits/stdc++.h>
#include "rabin_miller.cpp"
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto exponent = discrete_log(2,8,13);
  // Smallest exponent, including non-coprime a,m. Practical m limited by sqrt(m) memory.
  optional<int> discrete_log(int a, int b, int m) {
    assert(a >= 0 && b >= 0 && m > 0); a %= m; b %= m;
    if (b == 1 % m) return 0;
    int k = 1 % m, offset = 0;
    for (int g; (g = gcd(a, m)) > 1;) {
      if (b == k) return offset;
      if (b % g) return nullopt;
      b /= g; m /= g; k = mul_mod(k, a / g, m); ++offset;
    }
    int n = sqrtl(m) + 1; unordered_map<int, int> baby; int x = b;
    for (int q = 0; q <= n; ++q) { baby[x] = q; x = mul_mod(x, a, m); }
    int step = pow_mod(a, n, m); x = k;
    for (int p = 1; p <= n + 1; ++p) {
      x = mul_mod(x, step, m); auto it = baby.find(x);
      if (it != baby.end()) return p * n - it->second + offset;
    }
    return nullopt;
  }
//NOTEBOOK_END
}
