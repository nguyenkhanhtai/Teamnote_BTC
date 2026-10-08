#pragma once
#include <bits/stdc++.h>
namespace notebook::dp {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: MonotoneMinHull cht; cht.add(3,1); auto y = cht.query(2);
  // Add nonincreasing slopes; query nondecreasing x. Products fit int128;
  // coefficients fit int64 and their products/differences fit signed int128.
  struct MonotoneMinHull {
    struct Line {
      long long m, b;
      __int128 at(long long x) const { return __int128(m) * x + b; }
    }; deque<Line> q;
    void add(long long m, long long b) {
      Line c {m, b};
      if (!q.empty() && q.back().m == m) {
        if (q.back().b <= b) return;
        q.pop_back();
      }
      while (q.size() > 1) {
        auto a = q[q.size() - 2], z = q.back();
        if((__int128(z.b)-a.b)*(__int128(z.m)-c.m)<(__int128(c.b)-z.b)*(__int128(a.m)-z.m))break;
        q.pop_back();
      }
      q.push_back(c);
    }
    __int128 query(long long x) {
      assert(!q.empty());
      while (q.size() > 1 && q[0].at(x) >= q[1].at(x)) q.pop_front();
      return q.front().at(x);
    }
  };
//NOTEBOOK_END
}
