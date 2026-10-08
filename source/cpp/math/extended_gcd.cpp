#pragma once
#include <bits/stdc++.h>
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto b = extended_gcd(12,18); // b.gcd, b.x, b.y
  struct Bezout { __int128 gcd, x, y; };
  Bezout extended_gcd(long long a, long long b) {
    __int128 r = a, s = b, x = 1, u = 0, y = 0, v = 1;
    while (s) {
      __int128 q=r/s; tie(r,s)=pair {s,r-q*s}; tie(x,u)=pair {u,x-q*u};
      tie(y, v) = pair {v, y - q * v};
    }
    if (r < 0) r = -r, x = -x, y = -y;
    return {r, x, y};
  }
//NOTEBOOK_END
}
