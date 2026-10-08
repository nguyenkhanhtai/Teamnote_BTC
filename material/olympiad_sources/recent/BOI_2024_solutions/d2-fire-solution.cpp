/* TASK: The Holy Fire (fire)
 * Task proposal by: Sandra Schumann and Ahto Truu (EST)
 * Solution code by: Aldas Lenkšas (LTU SC)
 * Task also prepared by: Daumilas Ardickas (LTU SC)
 *
 * The task is to select the minimum number of intervals, such that the full circle
 * is covered by them. Circle length is M.
 *
 * Useful observation is that we can safely remove all the intervals that are fully covered 
 * by some other interval. They are not needed since we can always take the longer interval 
 * instead (that would cover the same interval, and possibly some more points). Note that if 
 * we have two same intervals (same beginning, same end), then we should keep one of them.
 *
 * This is not needed, but for simplicity, this solution changes intervals on the circle to the
 * intervals on the line (it makes some implementation parts easier). If the interval [s[i], e[i]]
 * is such that e[i] < s[i], then on the line it is the interval [s[i], e[i] + M]. Also, we
 * duplicate each of the intervals: each original interval [s[i], e[i]] gets a duplicate interval
 * [s[i] + M, e[i] + M]. To get the original answer (minimum number of intervals, such that the
 * full circle is covered), now it is enough to find minimum number of intervals on this line,
 * such that some continuous segment of length M is covered.
 *
 * The further solution assumes we are dealing with intervals on the line and no interval is 
 * fully covered by some other interval.
 *
 * Observe that for each interval i that we could take, there is some next best interval that
 * we would take. We can denote it as next[i].
 *
 * O(n^2) solution would start at some interval a, and then take b=next[a], then c=next[b], and so
 * on, until the segment of length M is taken. Then we can try another starting interval a.
 * We check all intervals as starting ones, and out of that we choose what we found to be the
 * minimum number of intervals to cover the segment of length M. 
 *
 * If by doing so we couldn't continuously cover a segment of length M, the answer is -1.
 *
 * To speed up this solution, we can add binary lifting to this. Now for each starting position,
 * we do (same as in binary search) checking "where would be the end, if we start from interval a, 
 * and take K intervals". We can find the minimum such K. This yields O(n log n) solution.
 *
 * Note: here we did not explain the binary lifting in great detail. You can check a better explanation
 * here: https://cp-algorithms.com/graph/lca_binary_lifting.html
 */


#include <bits/stdc++.h>

using namespace std;

const int MAXN = 4e5; // twice the contraints (since we duplicate intervals in modifyIntervals())
const int MAXK = 21; // ~log(MAXN), for binary lifting

long long n, m;
long long s[MAXN], e[MAXN];
int nextBest[MAXN];   // precalculated next best interval
int lift[MAXN][MAXK]; // precalculated binary lifting. lift[i][k] is taking 2^k intervals, starting from i-th one

void readInput() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> s[i] >> e[i];
	}
}

void removeUnnecessaryIntervals() {
	// interval is unnecessary if it is covered fully by other intervals

	int cnt = 0;

	// sort the intervals
	vector<pair<long long, long long>> intervals;
	for (int i = 0; i < n; i++) 
		intervals.push_back({s[i], -e[i]}); // this will help sort by increasing s[i], 
						    // and then by decreasing e[i]

	sort(intervals.begin(), intervals.end());

	long long furthestEnd = -1;

	for (auto interval : intervals) {
		long long start = interval.first;
		long long end = -interval.second;

		if (end <= furthestEnd) { 
			continue; // this interval is unnecessary
		}

		furthestEnd = end;
		s[cnt] = start;
		e[cnt] = end;
		cnt++;
	}

	n = cnt; // update interval count
}

void modifyIntervals() {
	// to make implementation a bit easier
	
	// deal with the cases of s > e
	for (int i = 0; i < n; i++) {
		if (s[i] > e[i]) e[i] += m;
	}

	// duplicate all intervals: (s, e) -> (s+m, e+m)
	for (int i = 0; i < n; i++) {
		s[i+n] = s[i] + m;
		e[i+n] = e[i] + m;
	}

	n *= 2; // since we duplicated

	removeUnnecessaryIntervals(); // remove covered fully by other intervals
}

void precalcNexts() {
	// sort intervals by their starts
	vector<pair<long long, int>> intervals; // vector of pairs {start, id}
	for (int i = 0; i < n; i++) 
		intervals.push_back({s[i], i});
	sort(intervals.begin(), intervals.end());

	// calculate nexts with two pointers technique
	int i = 0;

	for (auto interval : intervals) {
		int id = interval.second;
		
		while (i < n) {
			int intervalId = intervals[i].second;
			if (s[intervalId] > e[id])  // not overlapping
				break;
			i++;
		}

		nextBest[id] = intervals[i - 1].second;
	}
}

void precalcBinaryLifting() {
	for (int i = 0; i < n; i++) 
		lift[i][0] = nextBest[i];

	for (int k = 1; k < MAXK; k++) for (int i = 0; i < n; i++)
		lift[i][k] = lift[ lift[i][k-1] ][k-1];
}

int tryFrom(int startAdmin) {
	long long startTime = s[startAdmin];

	// do binary lifting (binary search) to find the furthest reachable admin
	// such that it would still not cover full circle
	
	int cntJumps = 0;
	int curAdmin = startAdmin;

	for (int i = MAXK-1; i >= 0; i--) {
		int jumpedToId = lift[curAdmin][i];
		if (e[jumpedToId] < (startTime + m)) { // does not cover full circle
			cntJumps += (1<<i); // 2^i
			curAdmin = jumpedToId;
		}
	}

	// we found the last before we get to full circle
	cntJumps++;
	curAdmin = lift[curAdmin][0];

	if (e[curAdmin] < (startTime + m)) {
		return -1; // impossible since we did not cover full circle
	}

	return cntJumps + 1;
}

int main() {
	readInput();
	modifyIntervals(); // see the explanation at the top
	precalcNexts(); 
	precalcBinaryLifting();

	int ans = -1;
	for (int i = 0; i < n; i++) {
		int curTaken = tryFrom(i);

		// update ans
		if (curTaken == -1) continue; 
		if (ans == -1 || curTaken < ans) ans = curTaken;
	}

	cout << ans << endl;


	return 0;
}

