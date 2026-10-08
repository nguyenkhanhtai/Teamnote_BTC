#pragma once
#include <bits/stdc++.h>
#include "rabin_miller.cpp"
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto exponent = discrete_log(2,8,13);
  // Smallest exponent, including non-coprime a,m. Practical m limited by sqrt(m) memory.
  optional<U64> discrete_log(U64 a, U64 b, U64 m) {
    assert(m); a %= m; b %= m;
    if (b == 1 % m) return 0;
    U64 k = 1 % m, offset = 0;
    for (U64 g; (g = gcd(a, m)) > 1;) {
      if (b == k) return offset;
      if (b % g) return nullopt;
      b /= g; m /= g; k = mul_mod(k, a / g, m); ++offset;
    }
    U64 n = sqrtl(m) + 1; unordered_map<U64, U64> baby; U64 x = b;
    for (U64 q = 0; q <= n; ++q) { baby[x] = q; x = mul_mod(x, a, m); }
    U64 step = pow_mod(a, n, m); x = k;
    for (U64 p = 1; p <= n + 1; ++p) {
      x = mul_mod(x, step, m); auto it = baby.find(x);
      if (it != baby.end()) return p * n - it->second + offset;
    }
    return nullopt;
  }
//NOTEBOOK_END
}
