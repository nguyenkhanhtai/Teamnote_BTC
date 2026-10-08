#pragma once
#include <bits/stdc++.h>
namespace notebook::strings {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: RollingHash h("abc"); auto hash = h.get(0,2);
  struct RollingHash {
    static constexpr int MOD=(static_cast<int>(1)<<61)-1; vector<int>h,p;
    static int mul(int a, int b) {
      __int128 x=(__int128)a*b; int v=(int)(x&MOD)+(int)(x>>61); return v>=MOD?v-MOD:v;
    }
    // Use the same base for hashes to be compared; equality is probabilistic. Randomize the shared base for adversarial inputs.
    RollingHash(string_view s,int base=911382323):h(s.size()+1),p(s.size()+1,1){
      assert(base > 256 && base < MOD);
      for (size_t i = 0; i < s.size(); ++i) {
        h[i+1]=(mul(h[i],base)+(unsigned char)s[i]+1)%MOD; p[i+1]=mul(p[i],base);
      }
    }
    int get(int l, int r) const {
      assert(0<=l&&l<=r&&r<(int)h.size()); return (h[r]+MOD-mul(h[l],p[r-l]))%MOD;
    }
  };
//NOTEBOOK_END
}
