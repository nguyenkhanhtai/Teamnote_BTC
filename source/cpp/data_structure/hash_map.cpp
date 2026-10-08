#pragma once
#include <bits/stdc++.h>
namespace notebook::data_structure {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: HashMap cnt; cnt.reserve(1000); ++cnt[42];
  struct SplitMixHash {
    uint64_t seed;
    SplitMixHash(uint64_t seed = 0x712367) : seed(seed) {}
    static uint64_t mix(uint64_t x) {
      x+=0x9e3779b97f4a7c15ULL; x=(x^(x>>30))*0xbf58476d1ce4e5b9ULL;
      x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL; return x ^ (x >> 31);
    }
    size_t operator()(uint64_t x) const { return mix(x + seed); }
  }; using HashMap = unordered_map<uint64_t,long long,SplitMixHash>;
  // Example: HashMap<int> counts(0,SplitMixHash(seed)); counts.reserve(expected_size);
//NOTEBOOK_END
}
