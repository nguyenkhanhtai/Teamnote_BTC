#pragma once
#include <bits/stdc++.h>
namespace notebook::strings {
  using namespace std;
//NOTEBOOK_BEGIN
  struct SuffixArray {
    vector<int> sa, rank, lcp;
    explicit SuffixArray(string_view s) {
      int n=s.size(),N=n+1; vector<int>a(N),c(N),p(N),cnt(max(N,257));
      for (int i = 0; i < n; ++i) a[i] = (unsigned char) s[i] + 1;
      for (int x : a) ++cnt[x];
      for (int i = 1; i < (int) cnt.size(); ++i) cnt[i] += cnt[i - 1];
      for (int i = N - 1; i >= 0; --i) p[--cnt[a[i]]] = i;
      int classes = 1;
      for (int i = 1; i < N; ++i) {
        if (a[p[i]] != a[p[i - 1]]) ++classes;
        c[p[i]] = classes - 1;
      }
      for (int k = 1; k < N; k *= 2) {
        vector<int> q(N), d(N); fill(cnt.begin(), cnt.end(), 0);
        for(int i=0; i<N; ++i){ q[i]=(p[i]-k+N)%N; ++cnt[c[q[i]]]; }
        for (int i = 1; i < classes; ++i) cnt[i] += cnt[i - 1];
        for (int i = N - 1; i >= 0; --i) p[--cnt[c[q[i]]]] = q[i];
        int nc = 1;
        for (int i = 1; i < N; ++i) {
          if (pair {c[p[i]], c[(p[i] + k) % N]}
          != pair {c[p[i - 1]], c[(p[i - 1] + k) % N]}) ++nc;
          d[p[i]] = nc - 1;
        }
        c.swap(d); classes = nc;
        if (k > N / 2) break;
      }
      sa.assign(p.begin() + 1, p.end()); rank.resize(n); lcp.resize(n);
      for (int i = 0; i < n; ++i) rank[sa[i]] = i;
      for (int i = 0, h = 0; i < n; ++i) {
        int r = rank[i];
        if (!r) { h = 0; continue; }
        int j = sa[r - 1];
        while (i + h < n && j + h < n && s[i + h] == s[j + h]) ++h;
        lcp[r] = h;
        if (h) --h;
      }
    }
  };
//NOTEBOOK_END
}
