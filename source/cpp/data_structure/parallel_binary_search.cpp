#pragma once
#include <bits/stdc++.h>
namespace notebook::data_structure {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto ans = parallel_binary_search(3,2,reset,apply,test);
  //      reset(): void; apply(eventID): void; test(queryID): bool.
  // Monotone test(query) after an event prefix. Returns first prefix length 0..M,
  // or M+1 if never true. reset() restores prefix 0; apply(i) applies event i.
  vector<int> parallel_binary_search(int M,int Q,function<void()> reset,
      function<void(int)> apply,function<bool(int)> test){
    assert(M >= 0 && Q >= 0); vector<int> lo(Q, 0), hi(Q, M + 1);
    for (;;) {
      vector<vector<int>> bucket(M + 1); bool active = false;
      for (int q = 0; q < Q; ++q) if (lo[q] < hi[q]) {
        active = true; bucket[(lo[q] + hi[q]) / 2].push_back(q);
      }
      if (!active) return lo;
      reset();
      for (int prefix = 0; prefix <= M; ++prefix) {
        if (prefix) apply(prefix - 1);
        for (int q : bucket[prefix]) if (test(q)) hi[q] = prefix;
        else lo[q] = prefix + 1;
      }
    }
  }
//NOTEBOOK_END
}
