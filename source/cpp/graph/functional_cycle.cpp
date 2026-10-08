#pragma once
#include <bits/stdc++.h>
namespace notebook::graph {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: long long nextState(long long x) { return (x+1)%3; }
  //      auto cycle = find_cycle(0,nextState);
  using CycleState = long long; // Change the state type if needed.
  struct CycleInfo {
    CycleState entry; size_t prefix_length, cycle_length;
  };
  // f must eventually cycle; equality compares complete states. O(1) extra space.
  CycleInfo find_cycle(CycleState start,function<CycleState(CycleState)> f){
    CycleState slow = f(start), fast = f(f(start));
    while (slow != fast) { slow = f(slow); fast = f(f(fast)); }
    size_t prefix = 0; slow = start;
    while (slow != fast) { slow = f(slow); fast = f(fast); ++prefix; }
    size_t length = 1; fast = f(slow);
    while (slow != fast) { fast = f(fast); ++length; }
    return {slow, prefix, length};
  }
//NOTEBOOK_END
}
