#pragma once
#include <bits/stdc++.h>
#include "pollard_rho.cpp"
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: mt19937_64 rng(123456); auto g = primitive_root(17,rng);
  U64 primitive_root(U64 p, mt19937_64 & rng) {
    assert(is_prime(p));
    if (p == 2) return 1;
    auto f=factorize(p-1,rng); f.erase(unique(f.begin(),f.end()),f.end());
    for (U64 g = 2; g < p; ++g) {
      bool ok = true;
      for (U64 q : f) if (pow_mod(g, (p - 1) / q, p) == 1) {
        ok = false; break;
      }
      if (ok) return g;
    }
    throw logic_error("prime required");
  }
//NOTEBOOK_END
}
