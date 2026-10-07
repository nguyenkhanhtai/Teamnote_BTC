#include "../source/cpp/utility/expression.cpp"
#include "../source/cpp/utility/johnson.cpp"
#include "../source/cpp/utility/calendar.cpp"
#include "../source/cpp/utility/josephus.cpp"
#include "../source/cpp/utility/bit_tricks.cpp"
#include "../source/cpp/utility/interactive.cpp"
using namespace std;
int main() {
    for (auto [text, expected] : vector<pair<string, long double>>{
            {"2^3^2",512}, {"-2^2",-4}, {"2^-2",.25}, {"(-2)^2",4},
            {"--3 + +2",5}, {"2 * -(3 + 4)",-14}, {".5 + 2e-1",.7},
            {"(-1 + 2)*(3+4)/2",3.5}})
        assert(fabsl(evaluate_expression(text)-expected)<1e-12L);
    for (const string text : {"", "()", "2+", "2 3", "1(2)", "(2", "2)", "1/*2", "."}) {
        bool rejected=false;
        try { evaluate_expression(text); } catch (const invalid_argument&) { rejected=true; }
        assert(rejected);
    }
    bool rejected=false;
    try { evaluate_expression("1/0"); } catch (const domain_error&) { rejected=true; }
    assert(rejected);
    mt19937 rng(20261007);
    for (int n=0;n<=7;++n) for (int trial=0;trial<20;++trial) {
        vector<FlowShopJob> jobs;
        for (int i=0;i<n;++i) jobs.push_back({i,static_cast<long long>(rng()%8),static_cast<long long>(rng()%8)});
        vector<int> perm(n); iota(perm.begin(),perm.end(),0);
        long long best=LLONG_MAX;
        do {
            long long a=0,b=0;
            for (int i:perm) { a+=jobs[i].first; b=max(a,b)+jobs[i].second; }
            best=min(best,b);
        } while (next_permutation(perm.begin(),perm.end()));
        assert(johnson_schedule(jobs).makespan==best);
    }
    assert(day_of_week(1970,1,1)==4);
    assert(day_of_week(2000,2,29)==2);
    assert(day_of_week(2026,10,7)==3);
    for (uint64_t n=1;n<=120;++n) for (uint64_t k=1;k<=150;++k) {
        vector<uint64_t> alive(n); iota(alive.begin(),alive.end(),0);
        size_t pos=0;
        while(alive.size()>1) { pos=(pos+k-1)%alive.size(); alive.erase(alive.begin()+pos); }
        assert(josephus_linear(n,k)==alive[0]);
        assert(josephus_fast(n,k)==alive[0]);
    }
    assert(josephus_fast(1000000000000ULL,1)==999999999999ULL);
    for (unsigned n=0;n<=10;++n) for(unsigned k=0;k<=n;++k) {
        vector<uint64_t> got,want;
        for_each_k_subset(n,k,[&](uint64_t x){got.push_back(x);});
        for (uint64_t x=0;x<(1ULL<<n);++x) if(popcount(x)==k) want.push_back(x);
        assert(got==want);
    }
    for (uint64_t mask=0;mask<128;++mask) {
        vector<uint64_t> got,want;
        for_each_submask(mask,[&](uint64_t x){got.push_back(x);});
        for(uint64_t x=mask;;--x) { if((x&mask)==x)want.push_back(x); if(!x)break; }
        assert(got==want);
    }
    vector<uint64_t> masks;
    for_each_k_subset(64,64,[&](uint64_t x){masks.push_back(x);});
    assert(masks==vector<uint64_t>{UINT64_MAX});
    masks.clear(); for_each_k_subset(64,1,[&](uint64_t x){masks.push_back(x);});
    assert(masks.size()==64 && masks.back()==(1ULL<<63));
    assert(trailing_zeros(0)==64 && leading_zeros(0)==64);
    for(int boundary=-20;boundary<=20;++boundary)
        assert(first_true(-21,21,[&](long long x){return x>=boundary;})==boundary);
    vector<int> walk{0,1,0,1,2,3,2,3,4};
    for(int x=0;x<=4;++x) assert(walk[find_unit_step_value(0,8,x,[&](long long i){return walk[i];})]==x);
    for(int n=2;n<=100;++n) {
        vector<int> a(n);iota(a.begin(),a.end(),0);shuffle(a.begin(),a.end(),rng);
        auto [best,second]=top_two(n,[&](int i,int j){return a[i]>a[j];});
        assert(a[best]==n-1 && a[second]==n-2);
    }
    istringstream input("7 -1");ostringstream output;
    InteractiveSession<int> session(input,output,2);
    assert(session.ask([](ostream& out){out<<"? 4";},[](int x){return x>=0;})==7);
    rejected=false;
    try {session.ask([](ostream& out){out<<"? 5";},[](int x){return x>=0;});}
    catch(const runtime_error&){rejected=true;}
    assert(rejected && session.queries()==2 && output.str()=="? 4\n? 5\n");
    session.answer([](ostream& out){out<<"! 7";});
    assert(output.str()=="? 4\n? 5\n! 7\n");
    cout<<"Utility interfaces and differential checks passed\n";
}
