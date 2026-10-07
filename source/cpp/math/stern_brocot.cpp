#pragma once
#include <bits/stdc++.h>
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  using SternPath = vector<pair<char, uint64_t>>;
  SternPath stern_encode(uint64_t p, uint64_t q) {
    assert(p && q && gcd(p, q) == 1); SternPath out;
    while (p != q) {
      if (p < q) {
        uint64_t k = (q - 1) / p; out.push_back( {'L', k}); q -= k * p;
      } else { uint64_t k=(p-1)/q; out.push_back( {'R',k}); p-=k*q; }
    }
    return out;
  }
  // Fractions and intermediate bounds must fit unsigned 128 bits.
  pair<__uint128_t, __uint128_t> stern_decode(const SternPath& path) {
    __uint128_t a = 0, b = 1, c = 1, d = 0;
    for (auto[dir, k] : path) {
      assert(k && (dir == 'L' || dir == 'R'));
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
