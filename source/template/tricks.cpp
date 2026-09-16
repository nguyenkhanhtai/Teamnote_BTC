mt19937 rd((unsigned)chrono::steady_clock:: now().time_since_epoch().count());
uniform_int_distribution<int> rnd_int(l, r); // rnd_int(rd)
uniform_real_distribution<double> rnd_real(0, 1);// rnd_real(rd)

// ext/pb_ds/assoc_container.hpp, tree_policy.hpp, rope
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T, typename Cmp = less<T>>
using ordered_set = tree <T, null_type, Cmp, rb_tree_tag, tree_order_statistics_node_update>;
//find_by_order(id), order_of_key(val)

bool next_combination(T &bit, int N){
T x = bit & -bit, y = bit + x;
bit = (((bit & ~y) / x) >> 1) | y;
return (bit < (1LL << N)); }
long long next_perm(long long v){
long long t = v | (v-1);
return (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(v) + 1));
} // __builtin_clz/ctz/popcount
for(submask=mask; submask; submask=(submask-1)&mask);
for(supermask=mask; supermask<(1<<n);
supermask=(supermask+1)|mask);
int frq(int n, int i) { int j, r = 0; // # of digit i in [1, n]
for (j = 1; j <= n; j *= 10) if (n / j / 10 >= !i) r += (n /
10 / j - !i) * j + (n / j % 10 > i ? j : n / j % 10 == i ? n %
j + 1 : 0);
return r; }
bitset<17> bs; bs[1] = bs[7] = 1; assert(bs._Find_first() == 1);
assert(bs._Find_next(0) == 1 && bs._Find_next(1) == 7);
assert(bs._Find_next(3) == 7 && bs._Find_next(7) == 17);
cout << bs._Find_next(7) << "\n";
template <int len = 1> // Arbitrary sized bitset
void solve(int n){ // solution using bitset<len>
if(len < n){ solve<std::min(len*2, MAXLEN)>(n); return; } }
//Fast IO / Fast Multiplication
namespace io { // thanks to cgiosy
const signed IS=1<<20; char I[IS+1],*J=I;
inline void daer(){if(J>=I+IS-64){
char*p=I;do*p++=*J++;
while(J!=I+IS);p[read(0,p,I+IS-p)]=0;J=I;}}
template<int N=10,typename T=int>inline T getu(){
daer();T x=0;int k=0;do x=x*10+*J-'0';
while(*++J>='0'&&++k<N);++J;return x;}
template<int N=10,typename T=int>inline T geti(){
daer();bool e=*J=='-';J+=e;return(e?-1:1)*getu<N,T>();}
struct f{f(){I[read(0,I,IS)]=0;}}flu; }; 
struct FastMod{ // typedef __uint128_t L;
ull b, m; FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
ull reduce(ull a){ // can be proven that 0 <= r < 2*b
ull q = (ull)((L(m) * a) >> 64), r = a - q * b;
return r >= b ? r - b : r;
} };
inline pair<uint32_t, uint32_t> Div(uint64_t a, uint32_t b){
if(__builtin_constant_p(b)) return {a/b, a%b};
uint32_t lo=a, hi=a>>32;
__asm__("div %2" : "+a,a" (lo), "+d,d" (hi) : "r,m" (b));
return {lo, hi}; // BOJ 27505, q r < 2^32
} // divide 10M times in ~400ms
ull mulmod(ull a, ull b, ull M){ // ~2x faster than int128
ll ret = a * b - M * ull(1.L / M * a * b);
return ret + M * (ret < 0) - M * (ret >= (ll)M);
} // safe for 0 ≤ a,b < M < (1<<63) when long double is 80bit
template<int D, typename T>
struct Vec : public vector<Vec<D - 1, T>> {
  static_assert(D >= 1, "Vector dimension must be greater than zero!");
  template<typename... Args>
  Vec(int n = 0, Args... args) : vector<Vec<D - 1, T>>(n, Vec<D - 1, T>(args...)) {
  }};template<typename T>
struct Vec<1, T> : public vector<T> {
  Vec(int n = 0, const T& val = T()) : vector<T>(n, val) {
  }
};
\\Kahan SUm of floating
float kahanSum(vector<float> nums) {
  float sum = 0.0f;
  float c = 0.0f;
  for (auto num : nums) {
    float y = num - c;
    float t = sum + y;
    c = (t - sum) - y;
    sum = t;
  }
  return sum;
}
//bitset-64 bit
#include <string>  #include <bits/functexcept.h>
#include <iosfwd> #include <bits/cxxabi_forced.h>
#include <bits/functional_hash.h>
#pragma push_macro("__SIZEOF_LONG__")
#pragma push_macro("__cplusplus")
#define __SIZEOF_LONG__ __SIZEOF_LONG_LONG__
#define unsigned unsigned long
#define __cplusplus 201102L
#define __builtin_popcountl __builtin_popcountll
#define __builtin_ctzl __builtin_ctzll
#include <bitset>
#pragma pop_macro("__cplusplus")
#pragma pop_macro("__SIZEOF_LONG__")
#undef unsigned
#undef __builtin_popcountl
#undef __builtin_ctzl