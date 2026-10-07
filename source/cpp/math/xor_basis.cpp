#pragma once
#include <bits/stdc++.h>
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  struct XorBasis {
    array<uint64_t, 64> b {}; int count = 0;
    bool insert(uint64_t x) {
      for (int i = 63; i >= 0; --i) if (x >> i & 1) {
        if (b[i]) x ^= b[i];
        else { b[i] = x; ++count; return true; }
      }
      return false;
    }
    int rank() const { return count; }
    bool contains(uint64_t x) const {
      for (int i = 63; i >= 0; --i) if (x >> i & 1) x ^= b[i];
      return x == 0;
    }
    uint64_t maximum(uint64_t x = 0) const {
      for (int i = 63; i >= 0; --i) x = max(x, x ^ b[i]);
      return x;
    }
    uint64_t minimum(uint64_t x = 0) const {
      for (int i = 63; i >= 0; --i) x = min(x, x ^ b[i]);
      return x;
    }
    optional<uint64_t> kth(uint64_t k) const {
      if (count < 64 && k >= (uint64_t(1) << count)) return nullopt;
      auto a = b; vector<uint64_t> v;
      for (int i = 0; i < 64; ++i) if (a[i]) {
        for (int j = 0; j < i; ++j) if (a[i] >> j & 1) a[i] ^= a[j];
        v.push_back(a[i]);
      }
      uint64_t x = 0;
      for (int i = 0; i < (int) v.size(); ++i) if (k >> i & 1) x ^= v[i];
      return x;
    }
  };
//NOTEBOOK_END
}
