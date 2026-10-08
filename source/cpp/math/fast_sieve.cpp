#pragma once
#include <bits/stdc++.h>
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto primes = segmented_sieve(2,1000000000,5000000);
  // Returns up to k primes in [L,R], in increasing order; R <= 1e9.
  const int SIEVE_BLOCK = 1000000;
  vector<int> segmented_sieve(int L,int R,int k = INT_MAX) {
    assert(0 <= L && L <= R && R <= 1000000000 && k >= 0);
    vector<int> base, primes;
    if (R < 2 || k == 0) return primes;
    int root = sqrtl(R);
    while ((root+1)*(root+1) <= R) ++root;
    vector<bool> small(root+1);
    for (int i = 2; i <= root; ++i) if (!small[i]) {
      base.push_back(i);
      for (int j = i*i; j <= root; j += i) small[j] = true;
    }
    bitset<SIEVE_BLOCK> composite;
    for (int lo = max<int>(L,2); lo <= R; lo += SIEVE_BLOCK) {
      int hi = min(R,lo+SIEVE_BLOCK-1);
      composite.reset();
      for (int p : base) {
        if (p*p > hi) break;
        int start = max(p*p,((lo+p-1)/p)*p);
        for (int j = start; j <= hi; j += p) composite[j-lo] = true;
      }
      for (int x = lo; x <= hi; ++x) if (!composite[x-lo]) {
        primes.push_back(x);
        if ((int)primes.size() == k) return primes;
      }
    }
    return primes;
  }
//NOTEBOOK_END
}
