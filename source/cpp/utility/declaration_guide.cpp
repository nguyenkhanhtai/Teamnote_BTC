#pragma once
#include <bits/stdc++.h>
#include "../data_structure/iterative_segment_tree.cpp"
#include "../graph/matroid_intersection.cpp"
using namespace std;
//NOTEBOOK_BEGIN
  int mergeSum(int a,int b) { return a+b; }
  bool atMostTwo(const vector<int>& ids) { return ids.size()<=2; }
  void declarationExample() {
    using namespace notebook::data_structure;
    using namespace notebook::graph;
    SegmentTree st({1,2,3},0,mergeSum);
    int sum = st.fold(0,3);
    MatroidIntersection mi(4,atMostTwo,atMostTwo);
    vector<int> ids = mi.solve();
    (void) sum; (void) ids;
  }
//NOTEBOOK_END
