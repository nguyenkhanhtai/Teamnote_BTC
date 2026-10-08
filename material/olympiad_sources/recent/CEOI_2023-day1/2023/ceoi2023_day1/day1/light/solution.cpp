#include<bits/stdc++.h>
#include"light.h"
typedef long long ll;
using namespace std;

ll N = 1;
vector<ll> act = {1};

void prepare() {
}

pair<ll, vector<ll>> solve(ll p) {
  vector<ll> ret = {N};
  ll x = N;
  while (x > 1) {
    x -= min(x - 1, N - x + 2);
    int i = upper_bound(act.begin(), act.end(), x) - act.begin() - 1;
    if (x - act[i] > p)
      x = act[i + 1];
    ret.insert(ret.begin(), x);
  }
  swap(ret, act);
  return {p, act};
}

pair<ll, vector<ll>> join(ll p) {
  N += p;
  return solve(p);
}

pair<ll, vector<ll>> leave(ll p) {
  N -= p;
  return solve(p);
}
