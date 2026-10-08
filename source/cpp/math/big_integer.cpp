#pragma once
#include <bits/stdc++.h>
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: bignum a{42,1}; print(a); // 1000000042
  // Nonnegative integer: base 10^9, least-significant block first.
  // Zero = {0}; otherwise the last block must be nonzero.
  // Example: 1234567890000000042 -> {42, 234567890, 1}.
  using bignum = vector<uint32_t>; constexpr uint32_t BASE = 1000000000;
  ostream & print(const bignum& a, ostream & out = cout) {
    // nonempty, normalized
    assert(!a.empty()); out << to_string(a.back());
    for (size_t i = a.size() - 1; i > 0; --i) {
      std::string block = to_string(a[i - 1]);
      out << std::string(9 - block.size(), '0') << block;
    }
    return out;
  }
//NOTEBOOK_END
}
