#include <bits/stdc++.h>

using namespace std;

char s[] = {'A', 'B'};
long long r[4];
vector<vector<char>> output;

int main() {
  cin >> r[0] >> r[1];

  int x = (r[0] < r[1] ? 0 : 1);
  while (r[x]) {
    if (r[x] % 2) {
      output.push_back({s[x ^ 1], 'C', 'C'});
      r[2] += r[x ^ 1];
    }
    output.push_back({s[x ^ 1], s[x ^ 1], s[x ^ 1]});
    r[x ^ 1] *= 2;
    r[x] /= 2;
  }

  cout << output.size() << endl;
  for (auto t : output) {
    cout << t[0] << " " << t[1] << " " << t[2] << endl;
  }

  cout << "C" << endl;
  return 0;
}
