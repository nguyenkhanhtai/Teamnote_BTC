#include <iostream>

using namespace std;

const int maxn = 1005;

long long a[maxn];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	string s;
	int x, y;
	for(int i = 1; i < n; i++) {
		cin >> s;
		if(s=="Josip") {
			cin >> x >> y;
			x--;
			a[i] = a[x] + y;
		}
		else {
			cin >> x;
			a[i] = x;
		}
	}
	int ind, mini = 2e9;
	for(int i = 0; i < n - 1; i++) {
		if(a[i + 1] - a[i] < mini) {
			mini = a[i + 1] - a[i];
			ind = i;
		}
	}
	cout << mini << ' ' << ind + 1 << ' ' << ind + 2 << '\n';
	return 0;
}
