#pragma once
#include <bits/stdc++.h>
#include "rabin_miller.cpp"
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto factors = factorize(360);
  inline mt19937 rho_rng(chrono::steady_clock::now().time_since_epoch().count());
  int rho_step(int v,int c,int n) {
    return static_cast<int>((__int128(mul_mod(v,v,n))+c)%n);
  }
  int rho_factor(int n, mt19937 & rng) {
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;
    for (;;) {
      uniform_int_distribution<int> random(1,n-1);
      int c=random(rng),y=random(rng),g=1,r=1,x=0,ys=0;
      
      while (g == 1) {
        x = y;
        for (int i = 0; i < r; ++i) y = rho_step(y,c,n);
        for (int k = 0; k < r && g == 1; k += 128) {
          ys = y; int q = 1;
          for(int i=0;i<min<int>(128,r-k);++i){ y=rho_step(y,c,n); q=mul_mod(q,x>y?x-y:y-x,n); }
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
  void factor_into(int n,mt19937& rng,vector<int>& out) {
    if (n==1) return;
    if (is_prime(n)) { out.push_back(n); return; }
    int d=rho_factor(n,rng); factor_into(d,rng,out); factor_into(n/d,rng,out);
  }
  vector<int> factorize(int n,mt19937& rng) {
    assert(n>=1); vector<int> out; factor_into(n,rng,out);
    sort(out.begin(),out.end()); return out;
  }
  vector<int> factorize(int n) { return factorize(n,rho_rng); }
//NOTEBOOK_END
}
