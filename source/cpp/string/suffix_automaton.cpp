#pragma once
#include <bits/stdc++.h>
namespace notebook::strings {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: SuffixAutomaton sam("banana");
  struct SuffixAutomaton {
    struct State {
      int length=0,link=-1; map<unsigned char,int>next; long long ends=0;
    }; vector<State> states {1}; int last = 0;
    void extend(unsigned char c) {
      int cur = states.size(); states.emplace_back();
      states[cur].length=states[last].length+1; states[cur].ends=1; int p=last;
      while(p>=0&&!states[p].next.count(c)){ states[p].next[c]=cur; p=states[p].link; }
      if (p < 0) states[cur].link = 0;
      else {
        int q = states[p].next[c];
        if(states[p].length+1==states[q].length)states[cur].link=q;
        else {
          int clone = states.size(); states.push_back(states[q]);
          states[clone].length=states[p].length+1; states[clone].ends=0;
          while(p>=0&&states[p].next[c]==q){ states[p].next[c]=clone; p=states[p].link; }
          states[q].link = states[cur].link = clone;
        }
      }
      last = cur;
    }
    SuffixAutomaton(string_view s = "") {
      for (unsigned char c : s) extend(c);
    }
    bool contains(string_view s) const {
      int u = 0;
      for (unsigned char c : s) {
        auto it = states[u].next.find(c);
        if (it == states[u].next.end()) return false;
        u = it->second;
      }
      return true;
    }
    long long distinct_substrings() const {
      long long ans = 0;
      for(int i=1;i<(int)states.size();++i)ans+=states[i].length-states[states[i].link].length;
      return ans;
    }
    // Returned counts do not mutate the automaton; may be recomputed after extensions.
    vector<long long> occurrences() const {
      vector<int>order(states.size()); iota(order.begin(),order.end(),0);
      vector<pair<int,int>> lengths;
      for (int id:order) lengths.push_back({states[id].length,id});
      sort(lengths.rbegin(),lengths.rend());
      for (int i=0;i<(int)order.size();++i) { order[i]=lengths[i].second; }
      vector<long long> cnt;
      for (auto& s : states) cnt.push_back(s.ends);
      for(int u:order)if(states[u].link>=0)cnt[states[u].link]+=cnt[u];
      return cnt;
    }
  };
//NOTEBOOK_END
}
