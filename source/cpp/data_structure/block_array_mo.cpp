#pragma once
#include <bits/stdc++.h>
namespace notebook::data_structure {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: BlockArray a({1,2,3});
  struct BlockArray {
    int n, block; vector<long long> a, lazy;
    BlockArray(vector<long long>values):n(values.size()),block(max(1,(int)sqrt(n))),a(move(values)),lazy((n+block-1)/block){}
    void add(int l, int r, long long x) {
      assert(0 <= l && l <= r && r <= n);
      while (l < r && l % block) a[l++] += x;
      while (l + block <= r) { lazy[l / block] += x; l += block; }
      while (l < r) a[l++] += x;
    }
    long long get(int i)const { assert(0<=i&&i<n); return a[i]+lazy[i/block]; }
  };
  uint64_t hilbert_order(uint32_t x,uint32_t y,int power,int rotation=0){
    assert(0 <= power && power <= 31);
    if (!power) return 0;
    uint32_t half=uint32_t(1)<<(power-1); int segment=x<half?(y<half?0:3):(y<half?1:2);
    segment=(segment+rotation)&3; static constexpr int delta[] {3,0,0,1};
    uint64_t size = uint64_t(1) << (2 * power - 2);
    auto sub=hilbert_order(x&(half-1),y&(half-1),power-1,(rotation+delta[segment])&3);
    return segment*size+((segment==1||segment==2)?sub:size-sub-1);
  }
  // Current range starts empty; add/remove receive array indices, answer receives query ID.
  vector<long long> mo_queries(int n,const vector<pair<int,int>>& ranges,
      function<void(int)> add,function<void(int)> remove,
      function<long long(int)> answer){
    int power = 0;
    while ((uint64_t(1) << power) <= (uint64_t) n) ++power;
    assert(power <= 31); vector<pair<uint64_t, int>> order;
    for (int id = 0; id < (int) ranges.size(); ++id) {
      auto[l, r] = ranges[id]; assert(0 <= l && l <= r && r <= n);
      order.push_back( {hilbert_order(l, r, power), id});
    }
    sort(order.begin(), order.end());
    vector<long long> result(ranges.size()); int l=0,r=0;
    for (auto[key, id] : order) {
      (void) key; auto[a, b] = ranges[id];
      while (l > a) add(--l);
      while (r < b) add(r++);
      while (l < a) remove(l++);
      while (r > b) remove(--r);
      result[id] = answer(id);
    }
    return result;
  }
//NOTEBOOK_END
}
