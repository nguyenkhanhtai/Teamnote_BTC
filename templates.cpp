#include<bits/stdc++.h>
bool VERBOSE = false;
// Use cerr (not std::cerr); false skips log expressions too.
#define cerr if (!VERBOSE) {} else std::cerr
#define FOR(i, a, b) for (int i = a; i <= b; i++)
#define FORD(i, a, b) for(int i = a; i >= b; i--)
#define endl '\n'
#define pb push_back
#define pf push_front
#define fastio ios_base::sync_with_stdio(NULL); cin.tie(NULL); cout.tie(NULL);

//Data structure
#define vi vector<int>
#define int long long
#define ii pair<int, int>
#define iii pair<int, ii>

//Bitmask (absolutely have a () outside of every thing)
#define LSB(x) (x & (-x))
#define ON(x, i) ((x >> i)&1)
#define OFF(x, i) !ON(x, i)
#define SET(x, i) ((x) |= (1LL << (i)))
#define UNSET(x, i) ((x) &= ~(1LL << (i)))

template<typename T> bool maximize(T &a, T b){    if (a < b){ a = b;  return true; }  return false; }
template<typename T> bool minimize(T &a, T b){    if (a > b){ a = b;  return true; }  return false; }
using namespace std;

const int MOD = 1e9 + 7;
void add(int &a, int b){
    a += b;
    if (a >= MOD) a -= MOD;
}

void sub(int &a, int b){
    a -= b;
    if (a < 0) a += MOD;
}
void solve(){
    
}
// Remember: return 0; at the end of main.
