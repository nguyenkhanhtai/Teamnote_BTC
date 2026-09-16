#define ull unsigned long long
ull Rho(ull n){
ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
auto f = [&](ull x) { return MulMod(x, x, n) + i; };
while(t++ % 40 || __gcd(prd, n) == 1){
if(x == y) x = ++i, y = f(x);
if((q = MulMod(prd, max(x,y) - min(x,y), n))) prd = q;
x = f(x), y = f(f(y));
} return __gcd(prd, n);
}
vector<ull> Factorize(ull n){ // sort?
if(n == 1) return {}; if(IsPrime(n)) return {n};
auto x = Rho(n); auto l=Factorize(x), r=Factorize(n/x);
l.insert(l.end(), r.begin(), r.end()); return l; }