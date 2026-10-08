#pragma once
#include <bits/stdc++.h>
namespace notebook::strings {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: AhoCorasick ac; ac.add("aba",0); ac.build();
  //      ac.scan("ababa",onMatch); // void onMatch(int end,int id)
  struct AhoCorasick {
    struct Node {
      array<int, 26> next; int link = 0, exit = -1; vector<int> ids;
      Node() { next.fill(-1); }
    }; vector<Node> t {1}; bool built = false;
    // Lowercase, nonempty patterns; IDs may repeat across different patterns.
    void add(string_view s, int id) {
      assert(!built && !s.empty()); int u = 0;
      for (char c : s) {
        assert('a' <= c && c <= 'z'); int x = c - 'a';
        if(t[u].next[x]<0){ t[u].next[x]=t.size(); t.emplace_back(); }
        u = t[u].next[x];
      }
      t[u].ids.push_back(id);
    }
    void build() {
      assert(!built); queue<int> q;
      for (int c = 0; c < 26; ++c) {
        int v = t[0].next[c];
        if (v < 0) t[0].next[c] = 0;
        else q.push(v);
      }
      while (!q.empty()) {
        int u=q.front(); q.pop(); int f=t[u].link; t[u].exit=t[f].ids.empty()?t[f].exit:f;
        for (int c = 0; c < 26; ++c) {
          int v = t[u].next[c];
          if (v < 0) t[u].next[c] = t[f].next[c];
          else { t[v].link = t[f].next[c]; q.push(v); }
        }
      }
      built = true;
    }
    // emit(end_exclusive, pattern_id); includes overlaps and duplicate patterns.
    void scan(string_view s,function<void(int,int)> emit) const {
      assert(built); int u = 0;
      for (int i = 0; i < (int) s.size(); ++i) {
        assert('a' <= s[i] && s[i] <= 'z'); u = t[u].next[s[i] - 'a'];
        for(int v=u; v>=0; v=t[v].exit)for(int id:t[v].ids)emit(i+1,id);
      }
    }
  };
//NOTEBOOK_END
}
