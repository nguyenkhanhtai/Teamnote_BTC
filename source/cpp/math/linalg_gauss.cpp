#pragma once
#include <bits/stdc++.h>
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto sol = gauss({{1.,2.,3.},{2.,1.,3.}},2);
  struct LinearSolution {
    int rank; bool consistent; vector<double>particular; vector<vector<double>>nullspace;
  };
  // Augmented n x (m+1) matrix; pivot tolerance depends on input scaling.
  LinearSolution gauss(vector<vector<double>>a,int m,double eps=1e-9){
    int n = a.size(), r = 0; vector<int> where(m, -1);
    for (auto& row : a) assert((int) row.size() == m + 1);
    for (int c = 0; c < m && r < n; ++c) {
      int p = r;
      for(int i=r+1; i<n; ++i)if(abs(a[i][c])>abs(a[p][c]))p=i;
      if (abs(a[p][c]) <= eps) continue;
      swap(a[p], a[r]); double t = a[r][c];
      for (int j = c; j <= m; ++j) a[r][j] /= t;
      for (int i = 0; i < n; ++i) if (i != r) {
        t = a[i][c];
        for (int j = c; j <= m; ++j) a[i][j] -= t * a[r][j];
      }
      where[c] = r++;
    }
    LinearSolution out { r, true, vector<double>(m), {} };
    for (int i = r; i < n; ++i) if (abs(a[i][m]) > eps) {
      out.consistent = false; return out;
    }
    for(int c=0; c<m; ++c)if(where[c]>=0)out.particular[c]=a[where[c]][m];
    else {
      vector<double> v(m); v[c] = 1;
      for(int j=0; j<m; ++j)if(where[j]>=0)v[j]=-a[where[j]][c];
      out.nullspace.push_back(v);
    }
    return out;
  }
  double determinant(vector<vector<double>> a, double eps = 1e-9) {
    int n = a.size(); double ans = 1;
    for (auto& row : a) assert((int) row.size() == n);
    for (int c = 0; c < n; ++c) {
      int p = c;
      for(int i=c+1; i<n; ++i)if(abs(a[i][c])>abs(a[p][c]))p=i;
      if (abs(a[p][c]) <= eps) return 0;
      if (p != c) swap(a[p], a[c]), ans = -ans;
      double pivot = a[c][c]; ans *= pivot;
      for (int i = c + 1; i < n; ++i) {
        double f = a[i][c] / pivot;
        for (int j = c + 1; j < n; ++j) a[i][j] -= f * a[c][j];
      }
    }
    return ans;
  }
//NOTEBOOK_END
}
