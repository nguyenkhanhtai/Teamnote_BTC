#pragma once
#include <bits/stdc++.h>
namespace notebook::data_structure {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: BinaryTrie tr; tr.insert(7); auto best = tr.max_xor(3);
  // Multiset of nonnegative int keys; duplicates and erasure supported.
  struct BinaryTrie {
    static constexpr int BITS = numeric_limits<int>::digits;
    struct Node { int child[2] {-1,-1}; int count=0; }; vector<Node>t {1};
    int size() const { return t[0].count; }
    int count(int x) const {
      assert(x >= 0);
      int u = 0;
      for (int b = BITS - 1; b >= 0; --b) {
        u = t[u].child[x >> b & 1];
        if (u < 0) return 0;
      }
      return t[u].count;
    }
    void insert(int x) {
      assert(x >= 0);
      int u = 0; ++t[u].count;
      for (int b = BITS - 1; b >= 0; --b) {
        int c = x >> b & 1, v = t[u].child[c];
        if (v < 0) { v = t.size(); t.emplace_back(); t[u].child[c] = v; }
        u = v; ++t[u].count;
      }
    }
    bool erase(int x) {
      if (!count(x)) return false;
      int u = 0; --t[u].count;
      for(int b=BITS-1; b>=0; --b){ u=t[u].child[x>>b&1]; --t[u].count; }
      return true;
    }
    optional<int> max_xor(int x) const {
      assert(x >= 0);
      if (!size()) return nullopt;
      int answer = 0; int u = 0;
      for (int b = BITS - 1; b >= 0; --b) {
        int c = x >> b & 1, v = t[u].child[c ^ 1];
        if(v>=0&&t[v].count){ answer|=static_cast<int>(1)<<b; u=v; }else u=t[u].child[c];
      }
      return answer;
    }
  };
//NOTEBOOK_END
}
