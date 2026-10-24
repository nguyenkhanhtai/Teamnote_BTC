#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
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

const int MAXN = 202;
int n, m, p, Q, L;
int sumA[MAXN][MAXN][MAXN], sumB[MAXN][MAXN][MAXN];
int sumC[MAXN][MAXN][MAXN];


void solve(){
    cin >> n >> m >> p >> Q >> L;

    FOR(i, 1, Q){
        int x1, y1, z1;
        int x2, y2, z2;
        int S, A, B, C;
        cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> S >> A >> B >> C;

        int dA = S, dB = 0, dC = 0;
        FOR(x, x1, x2){
            int c = dA;
            sumA[y1][z1][x] += c;
            sumA[y1][z2 + 1][x] -= c;
            sumA[y2 + 1][z1][x] -= c;
            sumA[y2 + 1][z2 + 1][x] += c;
            dA += A;
        }

        FOR(y, y1, y2){
            int c = dB;
            sumB[x1][z1][y] += c;
            sumB[x1][z2 + 1][y] -= c;
            sumB[x2 + 1][z1][y] -= c;
            sumB[x2 + 1][z2 + 1][y] +=c ;
            dB += B;
        }

        FOR(z, z1, z2){
            int c = dC;
            sumC[x1][y1][z] += c;
            sumC[x1][y2 + 1][z] -= c;
            sumC[x2 + 1][y1][z] -= c;
            sumC[x2 + 1][y2 + 1][z] += c;
            dC += C;
        }
    }

    FOR(i, 1, n){
        FOR(j, 1, m){
            FOR(k, 1, p){
                sumA[j][k][i] += sumA[j - 1][k][i] + sumA[j][k - 1][i] - sumA[j - 1][k - 1][i];
                sumB[i][k][j] += sumB[i - 1][k][j] + sumB[i][k - 1][j] - sumB[i - 1][k - 1][j];
                sumC[i][j][k] += sumC[i - 1][j][k] + sumC[i][j - 1][k] - sumC[i - 1][j - 1][k];
            }
        }
    }

    FOR(i, 1, L){
        int x, y, z;
        cin >> x >> y >> z;
        int res = sumA[y][z][x] + sumB[x][z][y] + sumC[x][y][z];
        cout << res << endl;
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
