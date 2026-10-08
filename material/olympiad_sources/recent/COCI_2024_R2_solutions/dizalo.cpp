#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

const int maxn = 1e5 + 5;

struct Logaritamska {
  int l[maxn];
  int (*merge)(int, int);
  Logaritamska(int (*f)(int, int)){
    merge = f;
  }
  void update(int x, int val) {
    for(; x < maxn; x += (x & -x)) {
      l[x] = merge(l[x], val);
    }
  }
  int query(int x) {
    int sol = 0;
    for(; x; x -= (x & -x)) {
      sol = merge(sol, l[x]);
    }
    return sol;
  }
};

int add(int x, int y) {
  return x + y;
}

int maks(int x, int y) {
  return max(x, y);
}

Logaritamska deleted_values(add), deleted_positions(add), active(add), compute(maks);
bool akt[maxn];
set < pair < int, int > > curr;
int a[maxn], pos[maxn];


int erased[maxn];
int queries[maxn];
vector < int > sw[maxn];

int calc(int x) {
  int val = a[x] - deleted_values.query(a[x]);
  int ind = x - deleted_positions.query(x);
  return ind - val;
}

int main() {
  int n, q;
  scanf("%d%d", &n, &q);
  for(int i = 1; i <= n; i++) {
    scanf("%d", a + i);
    pos[a[i]] = i;
    erased[i] = n + 1;
  }
  for(int i = 1; i <= q; i++) {
    scanf("%d", queries + i);
    erased[a[queries[i]]] = i;
  }
  int val;
  for(int i = 1; i <= n; i++) {
    val = compute.query(n + 1 - pos[i]);
    if(val < erased[i]) {
      sw[val].push_back(pos[i]);
      sw[erased[i]].push_back(-pos[i]);
      compute.update(n + 1 - pos[i], erased[i]);
    }
  }
  long long sol = 0;
  for(int i = 0; i <= q; i++) {
    if(i) {
      if(!akt[queries[i]]) {
        auto it = curr.lower_bound({a[queries[i]], 0});
        it--;
        sol -= active.query(it -> second) - active.query(queries[i]);
      }
      deleted_values.update(a[queries[i]], 1);
      deleted_positions.update(queries[i], 1);
    }
    for(int x : sw[i]) {
      if(x < 0) {
        akt[-x] = 0;
        curr.erase({a[-x], -x});
        active.update(-x, -1);
        sol -= calc(-x);
      }
      else {
        akt[x] = 1;
        curr.insert({a[x], x});
        active.update(x, 1);
        sol += calc(x);
      }
    }
    printf("%lld ", sol + n - i);
  }
  printf("\n");
  return 0;
}
