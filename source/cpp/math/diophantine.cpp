#pragma once
#include <bits/stdc++.h>
#include "extended_gcd.cpp"
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  struct DiophantineSolution { bool all_pairs; __int128 x, y, dx, dy; };
  // Every solution is (x+t*dx,y+t*dy), except all_pairs for 0x+0y=0.
  optional<DiophantineSolution>diophantine(long long a,long long b,long long c){
    auto z = extended_gcd(a, b);
    if (!z.gcd) {
      if (c) return nullopt;
      return DiophantineSolution {true, 0, 0, 0, 0};
    }
    if (c % z.gcd) return nullopt;
    return DiophantineSolution {
      false,z.x*(c/z.gcd),z.y*(c/z.gcd),b/z.gcd,-(__int128)a/z.gcd
    };
  }
//NOTEBOOK_END
}
