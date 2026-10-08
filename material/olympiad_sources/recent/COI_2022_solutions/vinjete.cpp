#include <bits/stdc++.h>

#define FOR(i, a, b) for (int i = (a); i < (b); i++)
#define REP(i, n) FOR(i, 0, n)
#define ll long long

using namespace std;

struct edge {
  int y;
  int a, b;
};

struct node {
  int val, sum;
  node *l, *r;

  node() {val = 0, sum = 0, l = r = NULL;}
};

const int OFF = (1 << 30);
const int MAXN = (1 << 17);
vector <node*> roots;

void update(int a, int b, int lo, int hi, node *x, node *y) {
  if (y->val != 0) {
    x->val = y->val;
    x->sum = x->val;
    return;
  }

  if (b <= lo || hi <= a) return;
  if (a <= lo && hi <= b) {
    x->val = (hi - lo);
    x->sum = x->val;
    return;
  }

  if (y->l == NULL) y->l = new node;
  if (y->r == NULL) y->r = new node;
  if (x->l == NULL) x->l = new node;
  if (x->r == NULL) x->r = new node;

  int mi = (lo + hi) / 2;

  if (mi <= a) {
    x->l = y->l;
  } else {
    update(a, b, lo, mi, x->l, y->l);
  }

  if (b <= mi) {
    x->r = y->r;
  } else {
    update(a, b, mi, hi, x->r, y->r);
  }

  x->sum = x->l->sum + x->r->sum;

  return;
}

int sol[MAXN];
vector <edge> ve[MAXN];

void dfs(int x, int par) {
  sol[x] = roots[x]->sum;

  for (auto tr : ve[x]) {
    if (tr.y == par) continue;
    update(tr.a - 1, tr.b, 0, OFF, roots[tr.y], roots[x]);
    dfs(tr.y, x);
  }

  return;
}

int main() {
  ios_base::sync_with_stdio(false);

  int n, m;
  cin >> n >> m;
  REP(i, n - 1) {
    int x, y, a, b;
    cin >> x >> y >> a >> b;
    x--, y--;
    ve[x].push_back({y, a, b});
    ve[y].push_back({x, a, b});
  }

  REP(i, n) roots.push_back(new node);
  dfs(0, 0);
  for (int i = 1; i < n; ++i) cout << sol[i] << "\n";

  return 0;
}
