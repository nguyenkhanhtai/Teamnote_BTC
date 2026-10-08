#pragma once
#include <bits/stdc++.h>
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto path = stern_encode(3,5); auto fraction = stern_decode(path);
  using SternPath = vector<pair<char, int>>;
  SternPath stern_encode(int p, int q) {
    assert(p > 0 && q > 0 && gcd(p, q) == 1); SternPath out;
    while (p != q) {
      if (p < q) {
        int k = (q - 1) / p; out.push_back( {'L', k}); q -= k * p;
      } else { int k=(p-1)/q; out.push_back( {'R',k}); p-=k*q; }
    }
    return out;
  }
  // Fractions and intermediate bounds must fit signed 128 bits.
  pair<__int128, __int128> stern_decode(const SternPath& path) {
    __int128 a = 0, b = 1, c = 1, d = 0;
    for (auto[dir, k] : path) {
      assert(k > 0 && (dir == 'L' || dir == 'R'));
      if (dir == 'L') c += k * a, d += k * b;
      else a += k * c, b += k * d;
    }
    return {a + c, b + d};
  }
  SternPath stern_lca(const SternPath& a, const SternPath& b) {
    SternPath out;
    for(size_t i=0; i<min(a.size(),b.size())&&a[i].first==b[i].first; ++i){
      out.push_back( {a[i].first, min(a[i].second, b[i].second)});
      if (a[i].second != b[i].second) break;
    }
    return out;
  }
//NOTEBOOK_END
}
