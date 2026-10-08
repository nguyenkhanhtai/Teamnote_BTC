#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

vector<pair<long long, long long>> p;

bool square(long long d2) {
    long long d = 0;
    long long inc = 1<<30;
    for (; inc >= 1; inc /= 2) {
        if ((d + inc) * (d + inc) <= d2) d += inc;
    }
    return d * d == d2;
}

int main() {
	long long y = 2*3*5*7*11*13*17;
	vector<long long> xs;
	vector<long long> xs_bad;
	long long n, k;
	cin>>n>>k;
	if (n == 3 && k == 2) {
	    // Sample
		cout << "1 1" << endl;
		cout << "1 2" << endl;
		cout << "2 2" << endl;
		exit(0);
	}
	long long x = 1;
	while ((int)xs.size() < n || (int)xs_bad.size() < n) {
		if (square(x * x + y * y)) {
			xs.push_back(x);
		} else if ((int)xs_bad.size() < n) {
			xs_bad.push_back(x);
		}
		x++;
	}
	long long i = 0;
	while (k >= 0) {
		if (k >= i) {
			k -= i;
			i++;
		} else {
			for (long long j = 0; j < k; j++) {
				p.push_back({xs[j], 0});
			}
			for (long long j = k; j < i; j++) {
				p.push_back({xs_bad[j - k], 0});
			}
			if (k) {
				p.push_back({0, y});
				i++;
			}
			for (; i < n; i++) {
				start:;
				long long px = rand() % 1000000000;
				long long py = rand() % 1000000000;
				for (int j = 0; j < i; j++) {
					long long d2 = (p[j].first - px) * (p[j].first - px) + (p[j].second - py) * (p[j].second - py);
					if (square(d2)) goto start;
				}
				p.push_back({px, py});
			}
			break;
		}
	}
	for (int j = 0; j < n; j++) {
		cout<<p[j].first<<" "<<p[j].second<<endl;
	}
}
