#include <bits/stdc++.h>

using namespace std;

int N;

int ask(int l, int r) {
  printf("? %d %d\n", l + 1, r + 1);
  fflush(stdout);
  int ret;
  scanf("%d", &ret);
  return ret;
}

void ans(int L) {
  printf("! %d\n", L);
  fflush(stdout);
}

int main(void) {
  scanf("%d", &N);

  int r_odd = 0, r_even = 0;
  for (int i = 0; i < N; ++i) {
    while (i - r_odd - 1 >= 0 && i + r_odd + 1 < N && ask(i - r_odd - 1, i + r_odd + 1)) ++r_odd;
    while (i - r_even >= 0 && i + r_even + 1 < N && ask(i - r_even, i + r_even + 1)) ++r_even;
  }

  ans(max(2 * r_odd + 1, 2 * r_even));
  return 0;
}
