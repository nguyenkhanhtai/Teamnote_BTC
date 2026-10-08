#pragma once
#include <bits/stdc++.h>
#include "pollard_rho.cpp"
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: mt19937 rng(123456); auto g = primitive_root(17,rng);
  int primitive_root(int p, mt19937 & rng) {
    assert(is_prime(p));
    if (p == 2) return 1;
    auto f=factorize(p-1,rng); f.erase(unique(f.begin(),f.end()),f.end());
    for (int g = 2; g < p; ++g) {
      bool ok = true;
      for (int q : f) if (pow_mod(g, (p - 1) / q, p) == 1) {
        ok = false; break;
      }
      if (ok) return g;
    }
    throw logic_error("prime required");
  }
//NOTEBOOK_END
}
