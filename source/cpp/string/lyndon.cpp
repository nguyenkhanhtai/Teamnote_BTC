#pragma once
#include <bits/stdc++.h>
namespace notebook::strings {
  using namespace std;
//NOTEBOOK_BEGIN
  vector<pair<int, int>> lyndon_factors(string_view s) {
    vector<pair<int, int>> out; int n = s.size();
    for (int i = 0; i < n;) {
      int j = i + 1, k = i;
      while (j < n && (unsigned char) s[k] <= (unsigned char) s[j]) {
        k = (unsigned char) s[k] < (unsigned char) s[j] ? i : k + 1; ++j;
      }
      while (i <= k) { out.push_back( {i, i + j - k}); i += j - k; }
    }
    return out;
  }
  int minimum_rotation(string_view s) {
    if (s.empty()) return 0;
    std::string t=std::string(s)+std::string(s); int n=s.size(),ans=0;
    for (int i = 0; i < n;) {
      ans = i; int j = i + 1, k = i;
      while (j < 2 * n && (unsigned char) t[k] <= (unsigned char) t[j]) {
        k = (unsigned char) t[k] < (unsigned char) t[j] ? i : k + 1; ++j;
      }
      while (i <= k) i += j - k;
    }
    return ans;
  }
//NOTEBOOK_END
}
