#pragma once
#include <bits/stdc++.h>
namespace notebook::math {
  using namespace std;
//NOTEBOOK_BEGIN
  // Use: auto c = convolution_fft({1,2},{3,4});
  // Rounded integer convolution; coefficient magnitudes must allow reliable double precision.
  using cd = complex<double>; const double PI = acos(-1);
  void fft(vector<cd>& a, bool invert) {
    int n = a.size(); assert(n > 0 && !(n & (n - 1)));
    for (int i = 1, j = 0; i < n; i++) {
      int bit = n >> 1;
      for (; j & bit; bit >>= 1) j ^= bit;
      j ^= bit;
      if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
      double ang=2*PI/len*(invert?-1:1); cd wlen(cos(ang),sin(ang));
      for (int i = 0; i < n; i += len) {
        cd w(1);
        for (int j = 0; j < len / 2; j++) {
          cd u = a[i + j], v = a[i + j + len / 2] * w; a[i + j] = u + v;
          a[i + j + len / 2] = u - v; w *= wlen;
        }
      }
    }
    if (invert) for (cd& x : a) x /= n;
  }
  vector<long long>convolution_fft(const vector<int>&a,const vector<int>&b){
    if (a.empty() || b.empty()) return {};
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int sz = 1, need = a.size() + b.size() - 1;
    while (sz < need) sz <<= 1;
    fa.resize(sz); fb.resize(sz); fft(fa, false); fft(fb, false);
    for (int i = 0; i < sz; i++) fa[i] *= fb[i];
    fft(fa, true); vector<long long> res(need);
    for (int i = 0; i < need; i++) res[i] = round(fa[i].real());
    return res;
  }
//NOTEBOOK_END
}
