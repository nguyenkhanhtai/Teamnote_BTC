#pragma once
#include <bits/stdc++.h>
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto count = prime_count(1000000);
  // Quotient-value sieve: O(N^(3/4)/log N) typical bound, O(sqrt N) storage.
  uint64_t prime_count(uint64_t n) {
    if (n < 2) return 0;
    uint64_t r = sqrtl(n);
    while ((__uint128_t)(r + 1) * (r + 1) <= n) ++r;
    while ((__uint128_t) r * r > n) --r;
    vector<uint64_t> v, g;
    for (uint64_t l = 1; l <= n;) {
      uint64_t x=n/l; v.push_back(x); g.push_back(x-1); uint64_t next=n/x;
      if (next == n) break;
      l = next + 1;
    }
    struct QuotientIndex {
      uint64_t n,r; size_t size;
      size_t get(uint64_t x) { return x<=r?size-x:n/x-1; }
    } index{n,r,v.size()};
    for (uint64_t p = 2; p <= r; ++p) {
      if (g[index.get(p)] == g[index.get(p - 1)]) continue;
      uint64_t before = g[index.get(p - 1)];
      for(size_t i=0;i<v.size()&&v[i]>=p*p;++i)g[i]-=g[index.get(v[i]/p)]-before;
    }
    return g[0];
  }
//NOTEBOOK_END
}
