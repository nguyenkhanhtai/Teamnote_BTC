#pragma once
#include <bits/stdc++.h>
namespace notebook::graph {
  using namespace std;
//NOTEBOOK_BEGIN
  template<typename State> struct CycleInfo {
    State entry; size_t prefix_length, cycle_length;
  };
  // f must eventually cycle; equality compares complete states. O(1) extra space.
  template<typename State,typename Next>CycleInfo<State>find_cycle(State start,Next f){
    State slow = f(start), fast = f(f(start));
    while (slow != fast) { slow = f(slow); fast = f(f(fast)); }
    size_t prefix = 0; slow = start;
    while (slow != fast) { slow = f(slow); fast = f(fast); ++prefix; }
    size_t length = 1; fast = f(slow);
    while (slow != fast) { fast = f(fast); ++length; }
    return {slow, prefix, length};
  }
//NOTEBOOK_END
}
