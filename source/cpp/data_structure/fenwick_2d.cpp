#pragma once
#include <bits/stdc++.h>
namespace notebook::data_structure {
  using namespace std;
//NOTEBOOK_BEGIN
  struct Fenwick2D {
    int n, m; vector<vector<long long>> t;
    Fenwick2D(int n,int m):n(n),m(m),t(n+1,vector<long long>(m+1)){
      assert(n >= 0 && m >= 0);
    }
    void add(int x, int y, long long value) {
      assert(0 <= x && x < n && 0 <= y && y < m);
      for(int i=x+1;i<=n;i+=i&-i)for(int j=y+1;j<=m;j+=j&-j)t[i][j]+=value;
    }
    long long prefix(int x, int y) const {
      assert(0 <= x && x <= n && 0 <= y && y <= m); long long ans = 0;
      for(int i=x; i; i-=i&-i)for(int j=y; j; j-=j&-j)ans+=t[i][j];
      return ans;
    }
    long long sum(int x1, int y1, int x2, int y2) const {
      assert(x1 <= x2 && y1 <= y2);
      return prefix(x2,y2)-prefix(x1,y2)-prefix(x2,y1)+prefix(x1,y1);
    }
  };
//NOTEBOOK_END
}
