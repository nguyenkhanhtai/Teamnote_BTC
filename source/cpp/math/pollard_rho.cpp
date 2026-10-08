#pragma once
#include <bits/stdc++.h>
#include "rabin_miller.cpp"
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: mt19937_64 rng(123456); auto factors = factorize(360,rng);
  U64 rho_step(U64 v,U64 c,U64 n) {
    return U64((U128(mul_mod(v,v,n))+c)%n);
  }
  U64 rho_factor(U64 n, mt19937_64 & rng) {
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;
    for (;;) {
      U64 c=rng()%(n-1)+1,y=rng()%(n-1)+1,g=1,r=1,x=0,ys=0;
      
      while (g == 1) {
        x = y;
        for (U64 i = 0; i < r; ++i) y = rho_step(y,c,n);
        for (U64 k = 0; k < r && g == 1; k += 128) {
          ys = y; U64 q = 1;
          for(U64 i=0;i<min<U64>(128,r-k);++i){ y=rho_step(y,c,n); q=mul_mod(q,x>y?x-y:y-x,n); }
          g = gcd(q, n);
        }
        r *= 2;
      }
      if (g == n) {
        do { ys = rho_step(ys,c,n); g = gcd(x > ys ? x - ys : ys - x, n); }
        while (g == 1);
      }
      if (g < n) return g;
    }
  }
  void factor_into(U64 n,mt19937_64& rng,vector<U64>& out) {
    if (n==1) return;
    if (is_prime(n)) { out.push_back(n); return; }
    U64 d=rho_factor(n,rng); factor_into(d,rng,out); factor_into(n/d,rng,out);
  }
  vector<U64> factorize(U64 n,mt19937_64& rng) {
    assert(n>=1); vector<U64> out; factor_into(n,rng,out);
    sort(out.begin(),out.end()); return out;
  }
//NOTEBOOK_END
}
