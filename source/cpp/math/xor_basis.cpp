#pragma once
#include <bits/stdc++.h>
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  // Nonnegative int values.
  // Use: XorBasis basis; basis.insert(7); auto best = basis.maximum();
  struct XorBasis {
    static constexpr int BITS = numeric_limits<int>::digits;
    array<int, BITS> b {}; int count = 0;
    bool insert(int x) {
      assert(x >= 0);
      for (int i = BITS - 1; i >= 0; --i) if (x >> i & 1) {
        if (b[i]) x ^= b[i];
        else { b[i] = x; ++count; return true; }
      }
      return false;
    }
    int rank() const { return count; }
    bool contains(int x) const {
      assert(x >= 0);
      for (int i = BITS - 1; i >= 0; --i) if (x >> i & 1) x ^= b[i];
      return x == 0;
    }
    int maximum(int x = 0) const {
      assert(x >= 0);
      for (int i = BITS - 1; i >= 0; --i) x = max(x, x ^ b[i]);
      return x;
    }
    int minimum(int x = 0) const {
      assert(x >= 0);
      for (int i = BITS - 1; i >= 0; --i) x = min(x, x ^ b[i]);
      return x;
    }
    optional<int> kth(int k) const {
      if (k < 0 || (count < BITS && k >= (static_cast<int>(1) << count))) return nullopt;
      auto a = b; vector<int> v;
      for (int i = 0; i < BITS; ++i) if (a[i]) {
        for (int j = 0; j < i; ++j) if (a[i] >> j & 1) a[i] ^= a[j];
        v.push_back(a[i]);
      }
      int x = 0;
      for (int i = 0; i < (int) v.size(); ++i) if (k >> i & 1) x ^= v[i];
      return x;
    }
  };
//NOTEBOOK_END
}
