#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <string>
#include <cmath>
#include <stack>
#include <list>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <numeric>
#include <utility>
#include <functional>
#include <limits>
#include <random>
#include <chrono>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;
typedef pair<int,int> pii;
typedef pair<int,ll> pil;
typedef vector<vector<int> > graph;

const double pi = acos(-1.0);

#define oned(a, x1, x2) { cout << #a << ":"; for(int _i = (x1); _i < (x2); _i++){ cout << " " << a[_i]; } cout << endl; }
#define twod(a, x1, x2, y1, y2) { cout << #a << ":" << endl; for(int _i = (x1); _i < (x2); _i++){ for(int _j = (y1); _j < (y2); _j++){ cout << (_j > y1 ? " " : "") << a[_i][_j]; } cout << endl; } }

#define mp make_pair
#define pb push_back
#define fst first
#define snd second

const int MAXN = 100005;

int p[MAXN], a[MAXN];

int rng(int i) {
	return rand()%i;
}

int query(int i, int j) {
	cout << "? " << p[i] << " " << p[j] << endl;
	int val; cin >> val;
	return val;
}

int main() {
	srand(time(0));
	
	int n; cin >> n;
	
	for(int i = 0; i < n; i++) {
		p[i] = i+1;
	}
	random_shuffle(p,p+n,rng);
	
	int id1 = 0, id2 = 1;
	int mx = query(id1,id2);
	for(int i = 2; i < n; i++) {
		int val = query(id1,i);
		if(val < mx) {
			a[p[i]] = val;
		} else if(val == mx) {
			a[p[id1]] = mx;
			id1 = i;
			mx = query(id1,id2);
		} else {
			a[p[id2]] = mx;
			id2 = i;
			mx = val;
		}
	}
	
	a[p[id1]] = a[p[id2]] = mx;
	
	cout << "!";
	for(int i = 1; i <= n; i++) {
		cout << " " << a[i];
	}
	cout << endl;
}