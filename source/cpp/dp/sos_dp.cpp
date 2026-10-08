#pragma once
#include <bits/stdc++.h>
namespace notebook::dp {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: vector<long long> f(1<<3,1); subset_transform(f);
  // In-place subset/superset zeta transform; inverse needs subtraction.
  void subset_transform(vector<long long>&a,bool supersets=false,bool inverse=false){
    size_t n = a.size(); assert(n && (n & (n - 1)) == 0);
    for(size_t bit=1;bit<n;bit<<=1)for(size_t mask=0;mask<n;++mask)if(bool(mask&bit)!=supersets){
      long long value = a[mask ^ bit];
      if (inverse) a[mask] -= value;
      else a[mask] += value;
    }
  }
//NOTEBOOK_END
}
