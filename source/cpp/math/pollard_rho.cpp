#pragma once
#include <bits/stdc++.h>
#include "rabin_miller.cpp"
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  U64 rho_factor(U64 n, mt19937_64 & rng) {
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;
    for (;;) {
      U64 c=rng()%(n-1)+1,y=rng()%(n-1)+1,g=1,r=1,x=0,ys=0;
      auto f=[&](U64 v){ return U64((U128(mul_mod(v,v,n))+c)%n); };
      while (g == 1) {
        x = y;
        for (U64 i = 0; i < r; ++i) y = f(y);
        for (U64 k = 0; k < r && g == 1; k += 128) {
          ys = y; U64 q = 1;
          for(U64 i=0;i<min<U64>(128,r-k);++i){ y=f(y); q=mul_mod(q,x>y?x-y:y-x,n); }
          g = gcd(q, n);
        }
        r *= 2;
      }
      if (g == n) {
        do { ys = f(ys); g = gcd(x > ys ? x - ys : ys - x, n); }
        while (g == 1);
      }
      if (g < n) return g;
    }
  }
  vector<U64> factorize(U64 n, mt19937_64 & rng) {
    assert(n >= 1); vector<U64> out;
    function<void(U64)> go = [&](U64 x) {
      if (x == 1) return;
      if (is_prime(x)) { out.push_back(x); return; }
      U64 d = rho_factor(x, rng); go(d); go(x / d);
    }; go(n); sort(out.begin(), out.end()); return out;
  }
//NOTEBOOK_END
}
