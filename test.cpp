#include<bits/stdc++.h>
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
#define SET(x, i) (x | (1LL << i))
#define UNSET(x, i) (SET(x, i) ^ (1LL << i))

#define TASKNAME "test"

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
    int n, m;
    cin >> n >> m;

    vector<int> a(n+1, 0), b(m+1, 0);
    int dif_gcd = 0;
    FOR(i, 1, n){
        cin >> a[i];
        if (i > 1) dif_gcd = __gcd(abs(a[i] - a[i - 1]), dif_gcd);
    }
    FOR(i, 1, m){
        cin >> b[i];
        cout << __gcd(abs(a[1] + b[i]), dif_gcd) << ' ';
    }


}
main(){
    fastio;
    if (fopen(TASKNAME".inp","r")){
        freopen(TASKNAME".inp","r",stdin);
        freopen(TASKNAME".out","w",stdout);
    }
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
}