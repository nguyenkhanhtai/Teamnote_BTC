// dummy, WA

#include <iostream>

using namespace std;

bool ask(int u, int v) {
    cout << "? " << u << " " << v << endl;
    char ans;
    cin >> ans;
    return ans == '>';
}

int main() {
    int n;
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i < j) cout << 1;
            else cout << 0;
        }
        cout << endl;
    }

    cout << "! ";
    for (int i = 1; i <= n; ++i) cout << i << " ";
    cout << endl;
}
