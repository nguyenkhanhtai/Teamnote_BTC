#pragma once
#include <bits/stdc++.h>
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto s = floor_sum(10,7,3,2); // sum floor((3*i+2)/7)
  // Nonnegative n,a,b; m>0. All intermediates and the result must fit signed 128 bits.
  __int128 floor_sum(uint64_t n, uint64_t m, uint64_t a, uint64_t b) {
    assert(m); __int128 ans = 0;
    for (;;) {
      if (a >= m) { ans += (__int128) n * (n - 1) / 2 * (a / m); a %= m; }
      if (b >= m) { ans += (__int128) n * (b / m); b %= m; }
      __uint128_t y = (__uint128_t) a * n + b;
      if (y < m) break;
      n = y / m; b = y % m; swap(m, a);
    }
    return ans;
  }
//NOTEBOOK_END
}
