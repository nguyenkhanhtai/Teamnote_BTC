#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<int,int> ii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ii> vii;
typedef vector<ll> vll;
typedef vector<pll> vpll;

#define PB push_back
#define PF push_front
#define PPB pop_back
#define PPF pop_front
#define X first
#define Y second
#define all(x) (x).begin(), (x).end()
#define rep(i, a, b) for(int i=a; i<b; i++)
#define sz(x) (int)(x).size()

const int mod = 1e9 + 7; //998244353;
const int inf = 1e9 + 7;
const ll INF = (ll)1e18 + 7;
const int logo = 20;
const int MAXN = 3e5 + 7;
const int off = 1 << logo;
const int trsz = off << 1;
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, -1, 1};

typedef long long ftype;
typedef pll point;

ftype dot(point a, point b) { return a.X * b.X + a.Y * b.Y; }
ftype f(point a, ftype x) { return dot(a, (pll){x, 1}); }

const int maxn = 1e5 + 2;

class LiChao{
public:
	point line[4 * maxn];
	vector<pair<point*, point>> change;
	
	LiChao() {
		for(int i=0; i<4*maxn; i++){
			line[i] = {0, INF};
		}
	}
	
	void rollback(){
		pair<pll*, pll> last = change.back();
		change.PPB();
		*last.X = last.Y;
	}
	
	void res(int psz){
		while(psz != (int)change.size()) rollback();
	}

	void add_line(point nw, int v = 1, int l = 0, int r = maxn) {
		int m = (l + r) / 2;
		bool lef = f(nw, l) < f(line[v], l);
		bool mid = f(nw, m) < f(line[v], m);
		if(mid) {
			change.PB({&line[v], line[v]});
			swap(line[v], nw);
		}
		if(r - l == 1) return;
		else if(lef != mid) add_line(nw, 2 * v, l, m);
		else add_line(nw, 2 * v + 1, m, r);
	}

	ftype get(int x, int v = 1, int l = 0, int r = maxn) {
		int m = (l + r) / 2;
			
		if(r - l == 1) return f(line[v], x);
		else if(x < m) return min(f(line[v], x), get(x, 2 * v, l, m));
		else return min(f(line[v], x), get(x, 2 * v + 1, m, r));
	}
}t[2];

struct node{
	int sz;
	pll vl;
	
	node(){
		sz = 0;
		vl = {0, 0};
	}
	
	node(int sz_, pll vl_) {
		sz = sz_;
		vl = vl_;
	}
}empt;

struct mono_stack{
	vector<node> st;
	int id;
	
	mono_stack(int x = 0) {
		id = x;
		st.clear();
	}
	
	pll pop(){
		pll vl = st.back().vl;
		st.PPB();
		
		int prosli = st.size() ? st.back().sz : 0;
		t[id].res(prosli);
		return vl;
	}
	
	
	void update(pll vl){
		point p = {vl.X, vl.Y};
		t[id].add_line(p);
		st.PB({(int)t[id].change.size(), vl});
	}
	
	ll query(int x){
		return t[id].get(x);
	}
};
 
 
struct mono_deque{
	mono_stack L, R;
	
	mono_deque() : L(0), R(1) {
		
	}
	
	void print(){
		for(auto &x : L.st) cout << "( " << x.vl.X <<  " " << x.vl.Y << ") ";
		for(auto &x : R.st) cout << "( " << x.vl.X <<  " " << x.vl.Y << ") ";
		cout << "\n";
	}
	
	void rebuild(){
		vector<pll> vl;
		vl.clear();
		for(auto &x : L.st) vl.PB(x.vl);
		reverse(all(vl));
		for(auto &x : R.st) vl.PB(x.vl);
		
		L.st.clear();
		t[0].res(0);
		t[1].res(0);
		R.st.clear();
		
		int mid = vl.size() / 2;
		for(int i=mid-1; i>=0; i--) L.update(vl[i]);
		for(int i=mid; i<(int)vl.size(); i++) R.update(vl[i]);
	}
	
	void push_front(pll vl){
		L.update(vl);
	}
	
	void push_back(pll vl){
		R.update(vl);
	}
	
	pll pop_front(){
		if(L.st.empty()) rebuild();
		if(L.st.empty()) return R.pop();
		return L.pop();
	}
	
	pll pop_back(){
		if(R.st.empty()) rebuild();
		if(R.st.empty()) return L.pop();
		return R.pop();
	}
	
	ll query(int x){
		ll first = -INF, second = -INF;
		if(!L.st.empty()) first = -L.query(x);
		if(!R.st.empty()) second = -R.query(x);
		return max(first, second);
	}
}dq;


ll p[MAXN], b[MAXN], z[MAXN], sumab[MAXN];
vi g[MAXN], cur;
int dep[MAXN], n, k;
ll ans = -INF;

pll tocka(int x) {
	pll ret = {(ll)sumab[x], (ll)-1 * (ll)z[x] * z[x]};
	return ret;
}

void dfs(int u, int par = 0) {
	cur.PB(u);
	dep[u] = par ? dep[par] + 1 : 0;
	sumab[u] = par ? ((ll)sumab[par] + b[par]) : 0;
	
	if(dep[u] > k) {
		dq.pop_front();
	}
	
	if(u != 1) dq.push_back(tocka(u));
	
	
	if(u != 1) {
		ans = max(ans, dq.query(z[u]) + z[u] * z[u] + z[u] * (sumab[u] + b[u]));
	}
	
	
	for(auto &x : g[u]) dfs(x, u);
	
	if(dep[u] > k) {
		dq.push_front(tocka(cur[cur.size() - 1 - k]));
	}
	
	
	if(u != 1) dq.pop_back();
	cur.PPB();
}

void solve(){
	cin >> n >> k;
	for(int i=2; i<=n; i++) cin >> p[i], g[p[i]].PB(i);
	for(int i=2; i<=n; i++) cin >> z[i];
	for(int i=2; i<=n; i++) cin >> b[i];
	dfs(1);
	cout << ans << "\n";
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int tt = 1;
	//cin >> tt;
	while(tt--) solve();
	return 0;
}

