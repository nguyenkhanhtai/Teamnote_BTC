#pragma once
#include <bits/stdc++.h>
namespace notebook::strings {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: de_bruijn(2,3,onDigit); // void onDigit(int digit)
  void de_bruijn(int k,int n,function<void(int)> emit) {
    assert(k >= 1 && n >= 1);
    if (k == 1) { emit(0); return; }
    vector<int> a(n + 1);
    struct DeBruijnDFS {
      int k,n; vector<int>& a; function<void(int)> emit;
      void go(int t,int p) {
        if (t > n) {
          if (n % p == 0) for (int i = 1; i <= p; ++i) emit(a[i]);
          return;
        }
        a[t] = a[t - p]; go(t + 1, p);
        for (int c = a[t - p] + 1; c < k; ++c) { a[t] = c; go(t + 1, t); }
    }
    } helper{k,n,a,emit}; helper.go(1, 1);
  }
//NOTEBOOK_END
}
