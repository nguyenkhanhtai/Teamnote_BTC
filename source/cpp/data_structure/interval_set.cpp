#pragma once
#include <bits/stdc++.h>
namespace notebook::data_structure {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: IntervalSet seg(0,10,0); seg.assign(2,5,7);
  // Complete interval partition of [lo,hi), adjacent equal values merged.
  // Assign takes O((erased_intervals+1)*log(number_of_intervals)) worst case.
  struct IntervalSet {
    struct Entry { int end; int value; }; map<int,Entry>segments;
    int lo, hi;
    auto split(int x) {
      if (x == hi) return segments.end();
      auto it = prev(segments.upper_bound(x));
      if (it->first == x) return it;
      int end=it->second.end; int value=it->second.value; it->second.end=x;
      return segments.emplace(x, Entry {end, move(value)}).first;
    }
    struct Interval { int l, r; int value; };
    IntervalSet(int lo,int hi,int initial):lo(lo),hi(hi){
      assert(lo < hi); segments.emplace(lo, Entry {hi, move(initial)});
    }
    const int& get(int x) const {
      assert(lo<=x&&x<hi); return prev(segments.upper_bound(x))->second.value;
    }
    void assign(int l, int r, int value) {
      assert(lo <= l && l <= r && r <= hi);
      if (l == r) return;
      auto right = split(r), left = split(l); segments.erase(left, right);
      auto it = segments.emplace(l, Entry {r, move(value)}).first;
      if (it != segments.begin()) {
        auto p = prev(it);
        if (p->second.value == it->second.value) {
          p->second.end = it->second.end; segments.erase(it); it = p;
        }
      }
      auto next = std::next(it);
      if(next!=segments.end()&&it->second.value == next->second.value){
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
