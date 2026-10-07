#pragma once
#include <bits/stdc++.h>
namespace notebook::data_structure {
  using namespace std;
//NOTEBOOK_BEGIN
  // Multiset of unsigned 64-bit keys; duplicates and erasure supported.
  struct BinaryTrie {
    struct Node { int child[2] {-1,-1}; int count=0; }; vector<Node>t {1};
    int size() const { return t[0].count; }
    int count(uint64_t x) const {
      int u = 0;
      for (int b = 63; b >= 0; --b) {
        u = t[u].child[x >> b & 1];
        if (u < 0) return 0;
      }
      return t[u].count;
    }
    void insert(uint64_t x) {
      int u = 0; ++t[u].count;
      for (int b = 63; b >= 0; --b) {
        int c = x >> b & 1, v = t[u].child[c];
        if (v < 0) { v = t.size(); t.emplace_back(); t[u].child[c] = v; }
        u = v; ++t[u].count;
      }
    }
    bool erase(uint64_t x) {
      if (!count(x)) return false;
      int u = 0; --t[u].count;
      for(int b=63; b>=0; --b){ u=t[u].child[x>>b&1]; --t[u].count; }
      return true;
    }
    optional<uint64_t> max_xor(uint64_t x) const {
      if (!size()) return nullopt;
      uint64_t answer = 0; int u = 0;
      for (int b = 63; b >= 0; --b) {
        int c = x >> b & 1, v = t[u].child[c ^ 1];
        if(v>=0&&t[v].count){ answer|=uint64_t(1)<<b; u=v; }else u=t[u].child[c];
      }
      return answer;
    }
  };
//NOTEBOOK_END
}
