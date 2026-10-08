#include <bits/stdc++.h>
#define int long long
using namespace std;

// Exact snippet from source/cpp/math/fast_sieve.cpp
  // Use: auto primes = segmented_sieve(2,1000000000,5000000);
  // Returns up to k primes in [L,R], in increasing order; R <= 1e9.
  const int SIEVE_BLOCK = 1000000;
  vector<int> segmented_sieve(int L,int R,int k = INT_MAX) {
    assert(0 <= L && L <= R && R <= 1000000000 && k >= 0);
    vector<int> base, primes;
    if (R < 2 || k == 0) return primes;
    int root = sqrtl(R);
    while ((root+1)*(root+1) <= R) ++root;
    vector<bool> small(root+1);
    for (int i = 2; i <= root; ++i) if (!small[i]) {
      base.push_back(i);
      for (int j = i*i; j <= root; j += i) small[j] = true;
    }
    bitset<SIEVE_BLOCK> composite;
    for (int lo = max<int>(L,2); lo <= R; lo += SIEVE_BLOCK) {
      int hi = min(R,lo+SIEVE_BLOCK-1);
      composite.reset();
      for (int p : base) {
        if (p*p > hi) break;
        int start = max(p*p,((lo+p-1)/p)*p);
        for (int j = start; j <= hi; j += p) composite[j-lo] = true;
      }
      for (int x = lo; x <= hi; ++x) if (!composite[x-lo]) {
        primes.push_back(x);
        if ((int)primes.size() == k) return primes;
      }
    }
    return primes;
  }


// Primality helpers specialized for this problem.
  // Dung int; them #define int long long neu can so 64-bit.
  const int base_prime[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
  const int rb_seed[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
// 32-bit root/neighbor candidates: residue products fit unsigned 64 bits.
const int small_seed[] = {2, 7, 61};
int power_small(int a,int e,int m) {
    int result=1;
    a%=m;
    while (e) {
        if (e&1) result=1ULL*result*a%m;
        a=1ULL*a*a%m;
        e>>=1;
    }
    return result;
}
bool is_prime(int n) {
    if (n<2) return false;
    for (int p : base_prime) if (n%p==0) return n==p;
    int d=n-1,s=0;
    while (d%2==0) { d>>=1; ++s; }
    for (int a : small_seed) {
        if (a%n==0) continue;
        int x=power_small(a,d,n);
        if (x==1 || x==n-1) continue;
        bool pass=false;
        for (int r=1;r<s;++r) {
            x=1ULL*x*x%n;
            if (x==n-1) { pass=true; break; }
        }
        if (!pass) return false;
    }
    return true;
}

// This problem allows n <= 1e19. Products of residues fit signed __int128.
const __int128 LIMIT = (__int128)1000000000000000000LL * 10;
vector<__int128> many_factors;

__int128 power_large(__int128 a,__int128 e,__int128 m) {
    unsigned long long mod = (unsigned long long)m;
    __int128 result = 1;
    a %= m;
    while (e) {
        if (e & 1) result = (__uint128_t)result*a % mod;
        a = (__uint128_t)a*a % mod;
        e >>= 1;
    }
    return result;
}
bool prime_large(__int128 n) {
    if (n < 2) return false;
    if (n <= 3162277660LL) return is_prime((int)n);
    for (int p : base_prime) if (n % p == 0) return n == p;
    __int128 d = n-1;
    int s = 0;
    while (d % 2 == 0) { d >>= 1; ++s; }
    for (int a : rb_seed) {
        __int128 x = power_large(a,d,n);
        if (x == 1 || x == n-1) continue;
        bool pass = false;
        for (int r=1;r<s;++r) {
            x = (__uint128_t)x*x % (unsigned long long)n;
            if (x == n-1) { pass=true; break; }
        }
        if (!pass) return false;
    }
    return true;
}
void prepare() {
    // For >=3 factors, Bertrand gives n > last_prime^3 / 8.
    // Thus last_prime < 4.4e6; sieving to 5e6 covers every factor.
    auto primes = segmented_sieve(2,5000000);
    for (int i=0;i+2<(int)primes.size();++i) {
        if ((__int128)primes[i]*primes[i+1]*primes[i+2] > LIMIT) break;
        __int128 product=1;
        for (int j=i;j<(int)primes.size();++j) {
            product *= primes[j];
            if (product > LIMIT) break;
            if (j>=i+2) many_factors.push_back(product);
        }
    }
    sort(many_factors.begin(),many_factors.end());
}
int cached_left=0,cached_right=0;
bool nice(__int128 n) {
    if (binary_search(many_factors.begin(),many_factors.end(),n)) return true;
    // The first small divisor must be the first prime of the consecutive pair.
    for (int p : base_prime) if (n % p == 0) {
        if (n == p) return true;
        int q=p+1;
        while (!is_prime(q)) ++q;
        return (__int128)p*q == n;
    }
    if (prime_large(n)) return true;
    if (n < 6) return false;
    int p = sqrtl(n);
    while ((__int128)(p+1)*(p+1) <= n) ++p;
    while ((__int128)p*p > n) --p;
    if (cached_left <= p && p <= cached_right && cached_left >= 2) {
        p=cached_left;
    } else {
        cached_right=p;
        if (p > 2 && p % 2 == 0) --p;
        while (!is_prime(p)) p -= p==3 ? 1 : 2;
        cached_left=p;
    }
    if (n % p != 0) return false;
    int q = p+1;
    if (q > 2 && q % 2 == 0) ++q;
    while (!is_prime(q)) q += 2;
    return (__int128)p*q == n;
}
vector<__int128> queries;
bool larger_query(int a,int b) { return queries[a]>queries[b]; }
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    prepare();
    int t;
    cin >> t;
    queries.resize(t);
    vector<int> order(t);
    vector<bool> answer(t);
    for (int i=0;i<t;++i) {
        string text;
        cin >> text;
        for (char c : text) queries[i]=queries[i]*10+c-'0';
        order[i]=i;
    }
    // Descending roots reuse a known prime-free interval; equal queries run once.
    sort(order.begin(),order.end(),larger_query);
    for (int i=0;i<t;++i) {
        int id=order[i];
        if (i && queries[id]==queries[order[i-1]]) answer[id]=answer[order[i-1]];
        else answer[id]=nice(queries[id]);
    }
    for (bool result : answer) cout << (result ? "NICE" : "UGLY") << '\n';
}
