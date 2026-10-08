#pragma once
#include <bits/stdc++.h>
#include "rabin_miller.cpp"
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto root = sqrt_mod(4,17);
  optional<U64> sqrt_mod(U64 a, U64 p) {
    assert(is_prime(p)); a %= p;
    if (p == 2 || a == 0) return a;
    if (pow_mod(a, (p - 1) / 2, p) != 1) return nullopt;
    if(p%4==3){ U64 x=pow_mod(a,p/4+1,p); return min(x,p-x); }
    U64 q = p - 1; int s = 0;
    while (!(q & 1)) q >>= 1, ++s;
    U64 z = 2;
    while (pow_mod(z, (p - 1) / 2, p) != p - 1) ++z;
    U64 c=pow_mod(z,q,p),x=pow_mod(a,(q+1)/2,p),t=pow_mod(a,q,p);
    while (t != 1) {
      int i = 0; U64 u = t;
      while (u != 1) { u = mul_mod(u, u, p); ++i; }
      U64 b=pow_mod(c,U64(1)<<(s-i-1),p); x=mul_mod(x,b,p); c=mul_mod(b,b,p);
      t = mul_mod(t, c, p); s = i;
    }
    return min(x, p - x);
  }
//NOTEBOOK_END
}
