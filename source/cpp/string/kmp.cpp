#pragma once
#include <bits/stdc++.h>
namespace notebook::strings {
  using namespace std;
//NOTEBOOK_BEGIN
  vector<int> prefix_function(string_view s) {
    vector<int> p(s.size());
    for (int i = 1; i < (int) s.size(); ++i) {
      int j = p[i - 1];
      while (j && s[i] != s[j]) j = p[j - 1];
      if (s[i] == s[j]) ++j;
      p[i] = j;
    }
    return p;
  }
  vector<int> kmp_matches(string_view text, string_view pattern) {
    vector<int> out;
    if (pattern.empty()) {
      for (int i = 0; i <= (int) text.size(); ++i) out.push_back(i);
      return out;
    }
    auto p = prefix_function(pattern); int j = 0;
    for (int i = 0; i < (int) text.size(); ++i) {
      while (j && text[i] != pattern[j]) j = p[j - 1];
      if (text[i] == pattern[j]) ++j;
      if(j==(int)pattern.size()){ out.push_back(i-j+1); j=p[j-1]; }
    }
    return out;
  }
//NOTEBOOK_END
}
