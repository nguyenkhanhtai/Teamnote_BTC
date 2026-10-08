#pragma once
#include <bits/stdc++.h>
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: bool prime = is_prime(1000000007);
  using U64 = uint64_t; using U128 = __uint128_t;
  U64 mul_mod(U64 a, U64 b, U64 m) { return U128(a) * b % m; }
  U64 pow_mod(U64 a, U64 e, U64 m) {
    assert(m); U64 r = 1 % m;
    for(a%=m; e; e>>=1,a=mul_mod(a,a,m))if(e&1)r=mul_mod(r,a,m);
    return r;
  }
  bool is_prime(U64 n) {
    if (n < 2) return false;
    for(U64 p:{2,3,5,7,11,13,17,19,23,29,31,37})if(n%p==0)return n==p;
    U64 d = n - 1; int s = 0;
    while (!(d & 1)) d >>= 1, ++s;
    for(U64 a:{2ULL,325ULL,9375ULL,28178ULL,450775ULL,9780504ULL,1795265022ULL}){
      if (a % n == 0) continue;
      U64 x = pow_mod(a, d, n);
      if (x == 1 || x == n - 1) continue;
      bool pass = false;
      for(int r=1;r<s;++r){ x=mul_mod(x,x,n); if(x==n-1){ pass=true; break; } }
      if (!pass) return false;
    }
    return true;
  }
//NOTEBOOK_END
}
