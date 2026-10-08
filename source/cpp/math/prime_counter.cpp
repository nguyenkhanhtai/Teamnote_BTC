#pragma once
#include <bits/stdc++.h>
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto count = prime_count(1000000);
  // Quotient-value sieve: O(N^(3/4)/log N) typical bound, O(sqrt N) storage.
  int prime_count(int n) {
    if (n < 2) return 0;
    int r = sqrtl(n);
    while ((__int128)(r + 1) * (r + 1) <= n) ++r;
    while ((__int128) r * r > n) --r;
    vector<int> v, g;
    for (int l = 1; l <= n;) {
      int x=n/l; v.push_back(x); g.push_back(x-1); int next=n/x;
      if (next == n) break;
      l = next + 1;
    }
    struct QuotientIndex {
      int n,r; size_t size;
      size_t get(int x) { return x<=r?size-x:n/x-1; }
    } index{n,r,v.size()};
    for (int p = 2; p <= r; ++p) {
      if (g[index.get(p)] == g[index.get(p - 1)]) continue;
      int before = g[index.get(p - 1)];
      for(size_t i=0;i<v.size()&&v[i]>=p*p;++i)g[i]-=g[index.get(v[i]/p)]-before;
    }
    return g[0];
  }
//NOTEBOOK_END
}
