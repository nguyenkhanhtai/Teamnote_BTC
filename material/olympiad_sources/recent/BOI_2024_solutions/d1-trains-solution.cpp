/* TASK: Train Journey (trains)
 * Task proposal by: Bohdan Feysa (UKR)
 * Task prepared by: Bohdan Feysa (UKR), Zigmas Bitinas (LTU SC), Aldas Lenkšas (LTU SC)
 * 
 * Task can be solved by square root decomposition. Let's choose a constant C = sqrt(N).
 * Now we do the Dynamic Programming solution, where dp[i] represents how many journies
 * can be made if we would end the journey at the i-th city.
 *
 * If d[i] >= C, then each dp[j] is increased by dp[i], where j = i + t * d[i]. This takes
 * O(N/C) time.
 *
 * If d[i] < C, then we store the value in the array, so that we can add this value later.
 *
 */


#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9+7;
const int MAXN = 1e5;
const int C = 400; // ~sqrt(MAXN)

int n;
long long d[MAXN], x[MAXN];
int dp[MAXN];
int acc[C][C]; // the value to add to dp
int addToAcc[MAXN][C]; // the value to add to accumulator

void addToAccumulator(long long i, int jump, int a) {
	// a is the value to add
	
	if (i >= n) 
		return; // not interested

	if (a < 0) // deal with subtractions 
		a = (a + MOD) % MOD; 

	addToAcc[i][jump] = (addToAcc[i][jump] + a) % MOD;
}

int main() {
	// read input
	cin >> n;
	for (int i = 0; i < n; i++) 
		cin >> d[i] >> x[i];

	dp[0] = 1; // base case

	for (int i = 0; i < n; i++) {
		for (int jump = 1; jump < C; jump++) {
			int m = i % jump;
			acc[jump][m] = (acc[jump][m] + addToAcc[i][jump]) % MOD;
			dp[i] = (dp[i] + acc[jump][m]) % MOD;
		}

		if (d[i] == 0) continue; // not working teleporter

		// sqrt decomposition
		if (d[i] < C) {
			int jump = d[i];

			addToAccumulator(i + jump, jump, dp[i]);
			addToAccumulator(i + jump * x[i] + jump, jump, -dp[i]);
		} else {
			for (int j = i + d[i], xu = 1; xu <= x[i] && j < n; xu++, j += d[i]) {
		        	dp[j] = (dp[j] + dp[i]) % MOD;
			}
		}
	}

	// ans = dp[0] + dp[1] + ... + dp[n-1]
	int ans = 0;
	for (int i = 0; i < n; i++) 
		ans = (ans + dp[i]) % MOD;

	cout << (ans % MOD) << endl;
	
	return 0;
}

