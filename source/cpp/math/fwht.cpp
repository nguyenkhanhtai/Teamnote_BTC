#pragma once
#include <bits/stdc++.h>
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  enum class Walsh {Xor, And, Or};
  // Integer inverse XOR requires exact division; values/intermediates must fit.
  void fwht(vector<long long>& a, Walsh kind, bool inverse = false) {
    size_t n = a.size(); assert(n && !(n & (n - 1)));
    for(size_t len=1;len<n;len*=2)for(size_t i=0;i<n;i+=2*len)for(size_t j=0;j<len;++j){
      auto& x = a[i + j]; auto& y = a[i + j + len];
      if (kind == Walsh::Xor) {
        long long u = x, v = y; x = u + v; y = u - v;
      }else if(kind==Walsh::Or){ y+=inverse?-x:x; }else { x+=inverse?-y:y; }
    }
    if (inverse && kind == Walsh::Xor) for (auto& x : a) {
      assert(x % (long long) n == 0); x /= n;
    }
  }
//NOTEBOOK_END
}
