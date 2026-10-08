#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define com complex<ld>
#define ld long double
#define ii pair<ll,ll>
#define vi vector<int>
#define vii vector<ii>
#define vc vector<char>
#define vs vector<string>
#define vd vector<ld>
#define vcom vector<com>
#define vld vector<ld>
#define vvld vector<vld>
#define vll vector<ll>
#define vvi vector<vi>
#define vvii vector<vii>
#define vvc vector<vc>
#define vvs vector<vs>
#define vvll vector<vll>
#define vvd vector<vd>
#define vvcom vector<vcom>
#define vvld vector<vld>
#define FOR(x,n) for(int x=0;x<(n);x++)
#define FORS(x,n) for(int x=1;x<=(n);x++)
#define FORE(x,a) for(auto &x: a)
#define FORT(x,a,b) for(int x=(a);x<(b);x++)
#define FORD(x,a,b) for(int x=(a);x>=(b);x--)
#define ALL(x) x.begin(),x.end()
#define REP(n) for(int _ = 0; _ < n; _++)
#define MT make_tuple
#define MP make_pair
#define pb push_back
#define F first
#define S second
#define vvvll vector<vvll>
#define sz(x) ((int)x.size())

#ifndef M_PI
#define M_PI (acosl(-1))
#endif

ld err(ld a, ld b)
{
	ld d = abs(b - a);
	ld m = max((ld)(1), max(abs(a),abs(b)));
	return d / m;
}



// kactl geometry
template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y = 0) : x(x), y(y) {}
    bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    P operator*(T d) const { return P(x * d, y * d); }
    P operator/(T d) const { return P(x / d, y / d); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
    ld dist() const { return sqrt((ld)dist2()); }
    // angle to x-axis in interval [-pi, pi]
    ld angle() const { return atan2(y, x); }
    P unit() const { return *this / dist(); } // makes dist()=1
    P perp() const { return P(-y, x); }
    P normal() const { return perp().unit(); }
    P rotate(ld a) const {
        return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
    }
    friend ostream& operator<<(ostream& os, P p) {
        return os << "(" << p.x << "," << p.y << ")";
    }
};
typedef Point<ld> Pd;
vector<Pd> ps;
ll k, n;
ld s,t;

vvld cmp;
vvld cb;

bool sweep(int u, ld cst, ld eps) {
    if(s*ps[u].dist() > cst) return false;
    vector<pair<ld,int>> e; // Events (Angle,change) where change is whether a new point was added or removed.
    FOR(v,n) {
        if(u == v) continue;
        if(cb[u][v] > cst) continue;
        Pd mp = (ps[u]+ps[v])/2;
        Pd dir = (ps[v]-ps[u]).perp().unit();
        ld lmi = -1e9, lma = cmp[u][v];
        ld rmi = cmp[u][v], rma = 1e9;

        while(err(lmi,lma) > eps) {
            ld md = (lmi + lma)/2;
            ld c = (mp + dir*md).dist()*s + (mp + dir*md - ps[u]).dist()*t;
            if(c < cst) {
                lma = md;
            } else {
                lmi = md;
            }
        }

        while(err(rmi,rma) > eps) {
            ld md = (rmi + rma)/2;
            ld c = (mp + dir*md).dist()*s + (mp + dir*md - ps[u]).dist()*t;
            if(c < cst) {
                rmi = md;
            } else {
                rma = md;
            }
        }
        //cout << rmi << " " << rma << " " << cmp[u][v] << endl;
        ld langle = (mp + dir*(lmi+lma)/2-ps[u]).angle();
        ld rangle = (mp + dir*(rmi+rma)/2-ps[u]).angle();

        //cout << " " << cst << " " << v << " " << langle << " " << rangle << endl;

        e.pb({langle,1});
        e.pb({rangle,-1});

        if(langle > rangle) { // Crosses starting point
            e.pb({-M_PI,1});
            e.pb({M_PI,-1});
        }
    }
    sort(ALL(e));
    int cr = 1;
    if(cr >= k) return true;
    //cout << e.size() << endl;
    FORE(v,e) {
        cr += v.S;
        if(cr >= k) {
            //cout << ps[u] << " " << cst << endl;
            return true;
        }
    }
    return false;
}

int main() {
    ll os, ot;
    cin >> k >> n >> os >> ot;
    
    s = os;
    t = ot;
    s /= t;
    t = 1;

    FOR(i, n) {
        int x, y;
        cin >> x >> y;
        ps.pb(Pd(x, y));
    }
    cb.resize(n,vld(n));
    cmp.resize(n,vld(n));
    cout << setprecision(12) << fixed;
    if (t <= s) {
        vd d(n);
        FOR(i, n) d[i] = ps[i].dist();
        sort(ALL(d));
        cout << d[k - 1] * ot << endl;
        return 0;
    }
    ld best = 2e18;
    mt19937_64 rng(0);
    shuffle(ps.begin(), ps.end(), rng);
    ld eps1 = 1e-7;
    ld eps2 = 1e-7;
    FOR(i,n) FOR(j,i) {
        if(i == j) continue;
        Pd mp = (ps[i]+ps[j])/2;
        Pd dir = (ps[j]-ps[i]).perp().unit();
        ld mi = -1e9, ma = 1e9;
        while(err(mi,ma) > eps2) {
            ld md1 = (2*mi + ma)/3;
            ld md2 = (mi + 2*ma)/3;
            ld c1 = (mp + dir*md1).dist()*s + (mp + dir*md1 - ps[i]).dist()*t;
            ld c2 = (mp + dir*md2).dist()*s + (mp + dir*md2 - ps[i]).dist()*t;
            //cout << mi << " " << ma << endl;
            if(c1 <= c2) {
                ma = md2;
            } else {
                mi = md1;
            }
        }
        cmp[i][j] = (mi + ma)/2;
        cb[i][j] = (mp + dir*cmp[i][j]).dist()*s + (mp + dir*cmp[i][j] - ps[i]).dist()*t;
        cb[j][i] = cb[i][j];
        cmp[j][i] = -cmp[i][j]; 
    }

    
    FOR(i, n){
        ld better = best * (1 - eps1);
		//ld better = best - eps2;
        //if (!sweep(i, better, eps1,0)) continue;
        if (!sweep(i, better,eps2)) continue;
        //cout << i << endl;
        //cout << ps[i] << " " << i << " " << sweep(i, better,eps2) << " " << better << endl;
        ld mic = 0, mac = better;
        while(err(mic,mac) > eps2) {
            ld md = (mic + mac) / 2;
            //cout << " " << md << " " << sweep(i, md, eps2) << endl;
            if (sweep(i, md, eps2)) {
                mac = md;
            } else {
                //cout << 0 << endl;
                mic = md;
            }
        }

        best = (mic + mac) / 2;
    }
    cout << best * ot << endl;
}
