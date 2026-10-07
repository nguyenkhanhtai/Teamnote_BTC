#pragma once
#include <bits/stdc++.h>
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  struct LinearSieve {
    vector<int> primes, spf, phi, mu;
    explicit LinearSieve(int n) : spf(n + 1), phi(n + 1), mu(n + 1) {
      assert(n >= 0);
      if (n) phi[1] = mu[1] = 1;
      for (int i = 2; i <= n; ++i) {
        if(!spf[i]){ spf[i]=i; primes.push_back(i); phi[i]=i-1; mu[i]=-1; }
        for (int p : primes) {
          if (p > n / i) break;
          spf[i * p] = p;
          if(i%p==0){ phi[i*p]=phi[i]*p; mu[i*p]=0; break; }
          phi[i * p] = phi[i] * (p - 1); mu[i * p] = -mu[i];
        }
      }
    }
  };
//NOTEBOOK_END
}
