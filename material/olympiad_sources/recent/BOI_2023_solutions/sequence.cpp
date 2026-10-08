#include <bits/stdc++.h>
using namespace std;

const int inf = 1.01e9;
int n;
vector<int> w;
vector<uint64_t> seed;


struct Set{
    int push(int x){
        int i = data.size();
        while(data[i-1] > x) --i;
        if(data[i-1] == x) return -1;
        data.insert(data.begin()+i, x);
        hash ^= seed[x];
        return i;
    }
    void pop(int i){
        if(i == -1) return;
        hash ^= seed[data[i]];
        data.erase(data.begin()+i);
    }
    void push_back(int x){
        hash ^= seed[x];
        data.push_back(x);
    }
    int pop_back(){
        int ret = data.back();
        data.pop_back();
        hash ^= seed[ret];
        return ret;
    }
    size_t size(){
        return data.size();
    }

    vector<int> data;
    uint64_t hash = 0;
};

template<typename S, typename T>
void xmin(S&a, T const&b){
    if(b < a) a = b;
}

unordered_map<uint64_t, int> cache;
int rec(Set &nums){
    if(nums.size() == 1) return w[1];
    auto& entry = cache[nums.hash];
    if(entry) return entry;
    const int k = nums.pop_back();
    int ret = inf;
    // try (k-1) -> k
    {
        int i = nums.push(k-1);
        xmin(ret, rec(nums));
        nums.pop(i);
    }
    // try (k/d), (d) -> k
    {
        for(int d=2; d*d <= k; ++d) if(k%d == 0){
            const int i = nums.push(d);
            const int j = nums.push(k/d);
            xmin(ret, rec(nums));
            nums.pop(j);
            nums.pop(i);
        }
    }
    nums.push_back(k);
    return entry = ret + w[k];
}


signed main(){
    cin >> n;
    w.resize(n);
    cache.max_load_factor(0.25);
    cache.reserve(1<<10);
    mt19937 rng(5215218952190ull);
    seed.resize(n+1);
    for(auto &e : seed) e = uniform_int_distribution<uint64_t>(0ull, ~0ull)(rng);
    for(auto &e : w) cin >> e;
    w.insert(w.begin(), -1);

    Set s{{1}};
    for(int i=1; i<=n; ++i){
        const int j = s.push(i);
        cout << rec(s) << "\n";
        s.pop(j);
    }

}
