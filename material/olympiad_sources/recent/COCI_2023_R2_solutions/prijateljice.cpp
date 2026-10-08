#include <bits/stdc++.h>
using namespace std;

int n, m;

vector <string> a(30), b(30);

int main() {
  cin >> n >> m;
  int start = 0;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    a[s[0] - 'a' + 1] = s;
    if (!i) {
      start = s[0] - 'a' + 1;
    }
  }
  for (int i = 0; i < m; i++) {
    string s;
    cin >> s;
    b[s[0] - 'a' + 1] = s;
  }

  const string ans[] = {"Leona", "Zoe"};

  a[start - 1] = "";
  b[start - 1] = "";
  for (int i = start; i < 'z' + 2; i++) {
    if (a[i] == "" && b[i - 1] > a[i - 1]) {
      cout << ans[1] << endl;
      return 0;
    }
    if (b[i] == "" && a[i - 1] > b[i - 1]) {
      cout << ans[0] << endl;
      return 0;
    }
  }

  assert(0);

  return 0;
}

