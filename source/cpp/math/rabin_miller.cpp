#pragma once
#include <bits/stdc++.h>
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  // Dung int; them #define int long long neu can so 64-bit.
  const int base_prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
  const int rb_seed32[] = {2, 7, 61};
  const int rb_seed[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
  int mul_mod(int a, int b, int m) {
    return (__int128) a * b % m;
  }
  int pow_mod(int a, int e, int m) {
    assert(a >= 0 && e >= 0 && m > 0);
    int r = 1 % m;
    a %= m;
    while (e) {
      if (e & 1) r = mul_mod(r, a, m);
      a = mul_mod(a, a, m);
      e >>= 1;
    }
    return r;
  }
  bool is_prime(int n) {
    if (n < 2) return false;
    for (int p : base_prime) if (n % p == 0) return n == p;
    int d = n - 1, s = 0;
    while (d % 2 == 0) d >>= 1, ++s;
    const int *bases = n < (1LL << 32) ? rb_seed32 : rb_seed;
    int count = n < (1LL << 32) ? 3 : 7;
    for (int i = 0; i < count; ++i) {
      int a = bases[i];
      if (a % n == 0) continue;
      int x = pow_mod(a, d, n);
      if (x == 1 || x == n - 1) continue;
      bool pass = false;
      for (int r = 1; r < s; ++r) {
        x = mul_mod(x, x, n);
        if (x == n - 1) { pass = true; break; }
      }
      if (!pass) return false;
    }
    return true;
  }
//NOTEBOOK_END
}
