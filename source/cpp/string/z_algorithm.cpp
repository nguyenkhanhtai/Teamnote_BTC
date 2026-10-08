#pragma once
#include <bits/stdc++.h>
namespace notebook::strings {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto z = z_function("ababa");
  vector<int> z_function(string_view s) {
    int n = s.size(); vector<int> z(n);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
      if (i < r) z[i] = min(r - i, z[i - l]);
      while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];
      if (i + z[i] > r) l = i, r = i + z[i];
    }
    if (n) z[0] = n;
    return z;
  }
//NOTEBOOK_END
}
