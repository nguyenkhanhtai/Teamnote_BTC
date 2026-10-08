#pragma once
#include <bits/stdc++.h>
namespace notebook::data_structure {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: ExpandableIndex idx(buildIndex); idx.insert(3);
  //      buildIndex(const vector<int>&): vector<int>.
  // Binary-counter buckets. Builder(const vector<Value>&) returns a static index by value.
  // visit(index) called once per occupied bucket; caller combines query results.
  struct ExpandableIndex {
    using Value = int;
    using Index = vector<Value>; // Replace with your static index type.
    function<Index(const vector<Value>&)> build;
    vector<vector<Value>> buckets; vector<optional<Index>> indices;
    ExpandableIndex(function<Index(const vector<Value>&)> builder) : build(move(builder)){}
    void insert(Value value) {
      vector<Value> carry; carry.push_back(move(value)); size_t level = 0;
      for (;; ++level) {
        if(level==buckets.size()){ buckets.emplace_back(); indices.emplace_back(); }
        if (buckets[level].empty()) {
          auto index = build(carry); buckets[level] = move(carry);
          indices[level].emplace(move(index)); break;
        }
        for (auto& x : buckets[level]) carry.push_back(move(x));
        buckets[level].clear(); indices[level].reset();
      }
    }
    void query(function<void(const Index&)> visit) const {
      for (const auto& index : indices) if (index) visit(*index);
    }
  };
//NOTEBOOK_END
}
