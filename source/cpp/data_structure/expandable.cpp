#pragma once
#include <bits/stdc++.h>
namespace notebook::data_structure {
  using namespace std;
//NOTEBOOK_BEGIN
  // Binary-counter buckets. Builder(const vector<T>&) returns a static index by value.
  // visit(index) called once per occupied bucket; caller combines query results.
  template<typename T, typename Builder> struct ExpandableIndex {
    using Index=decay_t<invoke_result_t<Builder,const vector<T>&>>; Builder build;
    vector<vector<T>> buckets; vector<optional<Index>> indices;
    explicit ExpandableIndex(Builder builder) : build(move(builder)){}
    void insert(T value) {
      vector<T> carry; carry.push_back(move(value)); size_t level = 0;
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
    template<typename Visit> void query(Visit visit) const {
      for (const auto& index : indices) if (index) visit(*index);
    }
  };
//NOTEBOOK_END
}
