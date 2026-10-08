#pragma once
#include <bits/stdc++.h>
#include "scc_tarjan.cpp"
namespace notebook::graph {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: TwoSAT sat(3); sat.add_or(sat.literal(0,true),
  //                                      sat.literal(1,false));
  //      auto ans = sat.solve(); // optional<vector<bool>>
  // Literal 2*v=true, 2*v+1=false. add_or accepts encoded literals.
  struct TwoSAT {
    vector<vector<int>> g;
    TwoSAT(int variables) : g(2 * variables) {}
    static int literal(int variable,bool value){ return 2*variable+!value; }
    void imply(int a,int b){ g[a].push_back(b); g[b^1].push_back(a^1); }
    void add_or(int a, int b) { imply(a ^ 1, b); }
    void force(int a) { add_or(a, a); }
    optional<vector<bool>> solve() const {
      auto s=strongly_connected_components(g); vector<bool>answer(g.size()/2);
      for (int v = 0; v < static_cast<int>(answer.size()); ++v) {
        if (s.component[2 * v] == s.component[2 * v + 1]) return nullopt;
        answer[v] = s.component[2 * v] < s.component[2 * v + 1];
      }
      return answer;
    }
  };
//NOTEBOOK_END
}
