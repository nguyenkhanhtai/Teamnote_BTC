#include <bits/stdc++.h>
using namespace std;

char mat[60][60];

int main () {
  int n, k;
  string l;
  cin >> n >> k >> l;
  
  for(int i=1; i<=n; i++){
    for(int j=1; j<=n; j++) mat[i][j] = '.';
  }
  
  int r = (n + 1) / 2, s = (n + 1) / 2;
  for(auto &x : l){
    if(x == 'L') s--;
    else if(x == 'R') s++;
    else if(x == 'U') r--;
    else if(x == 'D') r++;
    else{
      for(int i=1; i<=n; i++){
        for(int j=1; j<=n; j++){
          if(abs(i - r) + abs(j - s) < k){
            mat[i][j] = x;
          }
        }
      }
    }
    
    s = min(s, n);
    s = max(s, 1);
    r = min(r, n);
    r = max(r, 1);
  }
  
  for(int i=1; i<=n; i++){
    for(int j=1; j<=n; j++) cout << mat[i][j];
    cout << "\n";
  }
  
  return 0;
}

