// 32bit : 2, 7, 61 / ull MulMod, PowMod (cast __uint128_t)
// 64bit : 2, 325, 9375, 28178, 450775, 9780504, 1795265022
bool MillerRabin(ull n, ull a){
if(a % n == 0) return true; int cnt = __builtin_ctzll(n - 1);
ull p=PowMod(a, n>>cnt, n); if(p==1 || p+1==n) return true;
while(cnt--) if((p=MulMod(p,p,n)) == n - 1) return true;
return false;
}
bool IsPrime(ll n){
if(n <= 11) return hard_coding;
if(n % 2 == 0 || ... 3 5 7 11) return false;
for(int p : {comments}) if(!MillerRabin(n, p)) return false;
return true;
}