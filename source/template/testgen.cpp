#include <bits/stdc++.h>
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
long long rd(long long l, long long r) {
    return uniform_int_distribution<long long>(l, r)(rng);
}

const string NAME = "test";

void gen() {
    ofstream inp(NAME + ".inp");
    // Tự sinh input ở đây:
    
}

int main() {
    int ntest = 100;
    for (int i = 1; i <= ntest; i++) {
        gen();
        (void)!system(("./" + NAME).c_str());
        (void)!system(("./" + NAME + "_trau").c_str());
        
        if (system(("diff -w -B " + NAME + ".out " + NAME + ".trau.out > /dev/null").c_str()) != 0) {
            cout << "Test " << i << ": WRONG!\n";
            return 0;
        }
        cout << "Test " << i << ": CORRECT!\n";
    }
    cout << "All tests passed!\n";
    return 0;
}