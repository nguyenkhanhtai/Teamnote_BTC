#pragma once
#include <bits/stdc++.h>
namespace notebook::strings {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto radii = manacher("ababa"); // radii.odd, radii.even
  struct PalindromeRadii { vector<int> odd, even; };
  PalindromeRadii manacher(string_view s) {
    int n=s.size(); PalindromeRadii out {vector<int>(n),vector<int>(n)};
    for (int i = 0, l = 0, r = -1; i < n; ++i) {
      int k = i > r ? 1 : min(out.odd[l + r - i], r - i + 1);
      while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) ++k;
      out.odd[i] = k--;
      if (i + k > r) l = i - k, r = i + k;
    }
    for (int i = 0, l = 0, r = -1; i < n; ++i) {
      int k = i > r ? 0 : min(out.even[l + r - i + 1], r - i + 1);
      while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) ++k;
      out.even[i] = k--;
      if (i + k > r) l = i - k - 1, r = i + k;
    }
    return out;
  }
//NOTEBOOK_END
}
