#pragma once
#include <bits/stdc++.h>
namespace notebook::strings {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: PalindromeTree pt; for (char c : string("aba")) pt.append(c);
  //      auto counts = pt.occurrences();
  struct PalindromeTree {
    struct Node {
      int length, link; map<unsigned char, int> next; int ends = 0;
    }; vector<Node>nodes { {-1,0,{},0 },{ 0,0,{},0 } }; std::string text; int last=1;
    bool fits(int v,int i,unsigned char c) const {
      int j=i-1-nodes[v].length; return j>=0 && (unsigned char)text[j]==c;
    }
    int append(unsigned char c) {
      text += char(c); int i = text.size() - 1, u = last;

      while (!fits(u,i,c)) u = nodes[u].link;
      auto it = nodes[u].next.find(c);
      if (it != nodes[u].next.end()) last = it->second;
      else {
        int v=nodes.size(),length=nodes[u].length+2; nodes.push_back( { length,1,{},0 });
        nodes[u].next[c] = v;
        if (length > 1) {
          int p = nodes[u].link;
          while (!fits(p,i,c)) p = nodes[p].link;
          nodes[v].link = nodes[p].next.at(c);
        }
        last = v;
      }
      ++nodes[last].ends; return last;
    }
    vector<int> occurrences() const {
      vector<int> cnt;
      for (auto& v : nodes) cnt.push_back(v.ends);
      for(int i=(int)nodes.size()-1; i>=2; --i)cnt[nodes[i].link]+=cnt[i];
      return cnt;
    }
  };
//NOTEBOOK_END
}
