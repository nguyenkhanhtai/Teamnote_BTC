#pragma once
#include <bits/stdc++.h>
namespace notebook::data_structure {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: HashMap cnt; cnt.reserve(1000); ++cnt[42];
  // Signed 63-bit mixer: mask wide products instead of overflowing int.
  struct IntegerHash {
    int seed;
    IntegerHash(int seed = 0x712367) : seed(seed) {}
    static int mix(int x) {
      const int MASK = LLONG_MAX;
      x = ((__int128)(x & MASK) + 0x1e3779b97f4a7c15LL) & MASK;
      x = ((__int128)(x ^ (x >> 30)) * 0x3f58476d1ce4e5b9LL) & MASK;
      x = ((__int128)(x ^ (x >> 27)) * 0x14d049bb133111ebLL) & MASK;
      return x ^ (x >> 31);
    }
    size_t operator()(int x) const {
      int sign = x < 0 ? 0x517cc1b727220a95LL : 0;
      return mix((x & LLONG_MAX) ^ (seed & LLONG_MAX)) ^ sign;
    }
  };
  using HashMap = unordered_map<int,int,IntegerHash>;
  // Use: HashMap cnt(0,IntegerHash(seed)); cnt.reserve(expected_size);
//NOTEBOOK_END
}
