#pragma once
#include <bits/stdc++.h>
namespace notebook::dp {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto ans = aliens_exact(k,lo,hi,oracle);
  //      oracle(lambda): PenalizedResult{minCost, count}.
  struct PenalizedResult { long long value; int count; };
  // oracle(lambda) minimizes cost-lambda*count, breaking ties toward MORE count.
  // Exact-count optimum must be discrete convex, attainable; lo/hi bracket count=k.
  long long aliens_exact(int k,long long lo,long long hi,
      function<PenalizedResult(long long)> oracle){
    assert(lo <= hi && oracle(hi).count >= k);
    while (lo < hi) {
      long long mid=lo+static_cast<long long>((__int128(hi)-lo)/2);
      if (oracle(mid).count >= k) hi = mid;
      else lo = mid + 1;
    }
    auto result = oracle(lo); return result.value + lo * k;
  }
//NOTEBOOK_END
}
