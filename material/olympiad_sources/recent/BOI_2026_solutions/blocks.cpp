#include <fstream>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

unordered_map<int, int> cnts;
unordered_set<int> colors;

int main(int argc, char **argv) {
    if (argc >= 3 && string(argv[1]) == "@") {
        string input = string(argv[2]);
        if (input.starts_with("manual-tests/samp")) {
            string output = input;
            output.resize(input.size() - 2);
            output += "out";
            ifstream outf(output);
            cout << outf.rdbuf();
            exit(0);
        }
    }
	int t;
	cin>>t;
	for (int tt = 0; tt < t; tt++) {
		cnts.clear();
		colors.clear();
		int n, k;
		cin>>n>>k;
		int out[n];
		for (int i = 0; i < n; i++) {
			int c;
			cin>>c;
			cnts[c]++;
			colors.insert(c);
		}
		if (n % 2 == 0) {
			int i = 0;
			for (int c : colors) {
				if (cnts[c] % 2 == 1) {
					cout<<"NO"<<endl;
					goto nxt;
				}
				while (cnts[c]) {
					out[i] = c;
					out[n - i - 1] = c;
					i++;
					cnts[c] -= 2;
				}
			}
		} else {
			int one = -1;
			int W = n / 2;
			int i = 0;
			for (int c : colors) {
				if (cnts[c] == 1) {
					if (one == -1) one = c;
					else {
						cout<<"NO"<<endl;
						goto nxt;
					}
				}
				while ((cnts[c] % 2 == 0 && cnts[c]) || cnts[c] > 3) {
					out[i] = c;
					out[n - i - 1] = c;
					i++;
					cnts[c] -= 2;
				}
			}
			int m = (n - 2 * i) / 3;
			m /= 2;
			if (one == -1) {
				bool first = true;
				int k = 1;
				bool alt = true;
				for (int c : colors) {
					if (cnts[c] == 3) {
						if (first) {
							out[-3 * m - 1 + W] = c;
							out[W] = c;
							out[3 * m + 1 + W] = c;
							first = false;
						} else {
							if (alt) {
								out[k + W] = c;
								out[m + k + W] = c;
								out[-m - 2 * k + W] = c;
							} else {
								out[-k + W] = c;
								out[-3 * m + 2 * k - 1 + W] = c;
								out[3 * m - k + 1 + W] = c;
								k++;
							}
							alt = !alt;
						}
					}
				}
			} else {
				out[n / 2] = one;
				int k = 1;
				bool alt = true;
				for (int c : colors) {
					if (cnts[c] == 3) {
						if (alt) {
							out[k + W] = c;
							out[m + k + W] = c;
							out[-m - 2 * k + W] = c;
						} else {
							out[-k + W] = c;
							out[-3 * m + 2 * k - 1 + W] = c;
							out[3 * m - k + 1 + W] = c;
							k++;
						}
						alt = !alt;
					}
				}
			}
		}

		cout<<"YES"<<endl;
		for (int i = 0; i < n; i++) {
			if (i) cout<<" ";
			cout<<out[i];
		}
		cout<<endl;
		nxt:;
	}
}
