#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 2e5 + 5;

int a[maxn];
int l[maxn];
vector < int > dp;

bool cmp(int x, int y) {
  return a[x] < a[y];
}

int binary(int x) {
  int lo = 0, hi = dp.size(), mid;
  while(lo < hi) {
    mid = (lo + hi) / 2;
    if(dp[mid] < x) {
      lo = mid + 1;
    }
    else {
      hi = mid;
    }
  }
  return lo;
}

void dodaj(int x) {
  int ind = binary(x);
  if(ind == dp.size()) {
    dp.push_back(x);
  }
  else {
    dp[ind] = x;
  }
}

int main() {
  int n;
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    scanf("%d", a + i);
    a[i]--;
  }
  int b;
  for(int i = 0; i < n; i++) {
    scanf("%d", &b);
    l[a[i]] = b;
  }
  for(int i = 0; i < n; i++) {
    dodaj(l[i]);
  }
  printf("%d\n", dp.size());
  return 0;
}

