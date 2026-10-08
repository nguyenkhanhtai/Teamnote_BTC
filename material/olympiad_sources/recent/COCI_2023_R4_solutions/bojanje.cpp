// Was hinter mir liegt ist vorbei, endlich frei!

#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for(int i = 0; i < (n); i++)
typedef long long int ll;

const int mod = 1e9 + 7;
const int pr[] = {1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

int add(int a, int b) {
    a += b;
    if(a >= mod) a -= mod;
    if(a < 0) a += mod;
    return a;
}

int mult(int a, int b) {
    return (ll)a * b % mod;
}

int pot(int a, int b) {
    int ret = 1;
    while(b) {
	if(b & 1) ret = mult(ret, a);
	a = mult(a, a);
	b >>= 1;
    }
    return ret;
}

int dij(int a, int b) {
    return mult(a, pot(b, mod - 2));
}

struct mat {
    int n;
    vector <vector <int> > m;
    mat(int _n) {
	n = _n;
	m.resize(n, vector <int>(n, 0));
    }
    void pov() {
	REP(i, n) m[i].push_back(0);
	m.push_back(vector <int>(n + 1, 0));
	n++;
    }
    mat operator *(mat a) {
	mat ret(n);
	REP(i, n) {
	    REP(j, n) {
		REP(k, n) {
		    ret.m[i][j] = add(ret.m[i][j], mult(m[i][k], a.m[k][j]));
		}
	    }
	}
	return ret;
    }
    mat pot(ll a) {
	mat ret(n), tr = *this;
	REP(i, n) ret.m[i][i] = 1;
	while(a) {
	    if(a & 1) ret = ret * tr;
	    tr = tr * tr;
	    a >>= 1;
	}
	return ret;
    }
};

int n, ind = 1;
map <int, int> saz;
vector <int> kom;

void rek(int zad, int ost, mat &op) {
    if(!ost) {
	int trh = 1, m = (int)kom.size();
	REP(i, m) trh *= pr[kom[i]];
	if(!saz[trh]) {
	    saz[trh] = ind;
	    ind++;
	    op.pov();
	}
	REP(i, m) {
	    REP(j, m) {
		int noh = trh;
		if(i != j) {
		    noh /= pr[kom[i]] * pr[kom[j]];
		    noh *= pr[kom[i] - 1] * pr[kom[j] + 1];
		}
		if(!saz[noh]) {
		    saz[noh] = ind;
		    ind++;
		    op.pov();
		}
		op.m[saz[noh] - 1][saz[trh] - 1] = add(op.m[saz[noh] - 1][saz[trh] - 1], dij(mult(kom[i], kom[j]), mult(n, n)));
	    }
	}
	return;
    }
    for(int i = zad; i <= ost / 2; i++) {
	kom.push_back(i);
	rek(i, ost - i, op);
	kom.pop_back();
    }
    kom.push_back(ost);
    rek(ost, 0, op);
    kom.pop_back();
    return;
}

int main() {
    int m, rj = 0;
    ll t;
    cin >> n >> t >> m;
    mat op(0);
    rek(1, n, op);
    op = op.pot(t);
    for(pair <int, int> p : saz) {
	int tr = 0;
	for(int i = 1; i <= n; i++) {
	    while(p.first % pr[i] == 0) {
		p.first /= pr[i];
		tr++;
	    }
	}
	if(tr >= m) rj = add(rj, op.m[p.second - 1][saz[1 << n] - 1]);
    }
    cout << rj << "\n";
    return 0;
}
