#pragma once
#include <bits/stdc++.h>
namespace notebook::data_structure {
  using namespace std;
//NOTEBOOK_BEGIN
  // Complete interval partition of [lo,hi), adjacent equal values merged.
  // Assign takes O((erased_intervals+1)*log(number_of_intervals)) worst case.
  template<typename T, typename Equal = equal_to<T>> struct IntervalSet {
    struct Entry { long long end; T value; }; map<long long,Entry>segments;
    long long lo, hi; Equal equal;
    auto split(long long x) {
      if (x == hi) return segments.end();
      auto it = prev(segments.upper_bound(x));
      if (it->first == x) return it;
      long long end=it->second.end; T value=it->second.value; it->second.end=x;
      return segments.emplace(x, Entry {end, move(value)}).first;
    }
    struct Interval { long long l, r; T value; };
    IntervalSet(long long lo,long long hi,T initial,Equal eq=Equal {}):lo(lo),hi(hi),equal(move(eq)){
      assert(lo < hi); segments.emplace(lo, Entry {hi, move(initial)});
    }
    const T& get(long long x) const {
      assert(lo<=x&&x<hi); return prev(segments.upper_bound(x))->second.value;
    }
    void assign(long long l, long long r, T value) {
      assert(lo <= l && l <= r && r <= hi);
      if (l == r) return;
      auto right = split(r), left = split(l); segments.erase(left, right);
      auto it = segments.emplace(l, Entry {r, move(value)}).first;
      if (it != segments.begin()) {
        auto p = prev(it);
        if (equal(p->second.value, it->second.value)) {
          p->second.end = it->second.end; segments.erase(it); it = p;
        }
      }
      auto next = std::next(it);
      if(next!=segments.end()&&equal(it->second.value,next->second.value)){
        it->second.end = next->second.end; segments.erase(next);
      }
    }
    vector<Interval> intervals() const {
      vector<Interval> out;
      for (auto& [l, e] : segments) out.push_back( {l, e.end, e.value});
      return out;
    }
  };
//NOTEBOOK_END
}
