#include <bits/stdc++.h>

using namespace std;

const long long mod = 1000000007;

int n;

vector<long long> powers_of_2;
vector<int> values;

struct Node {
    // sum[0] represents the sum of right(p)+1, sum[1] represents the sum of (-left(p)).
    long long sum[2] = {0, 0};
    // For each type of calculation (right and left), the number of times the value is to be multiplied by 2 and by 0.
    long long update[2][2] = {{0, 0},
                              {0, 0}};

    long long GetValue(int index) {
        // If we have multiplication by zero, the answer is also zero.
        if (update[index][0])return 0;
        return powers_of_2[update[index][1]] * sum[index] % mod;
    }
};

vector<Node> nodes;

void RefreshNode(int node, int index) {
    nodes[node].sum[index] = (nodes[node * 2 + 1].GetValue(index) + nodes[node * 2 + 2].GetValue(index)) % mod;
}

void Update(int node, int beg, int end, int target_start, int target_end, int upd_index, int upd_value) {
    if (beg >= target_start && end <= target_end) {
        if (upd_value == 2) {
            nodes[node].update[upd_index][1]++;
        } else if (upd_value == 1) {
            nodes[node].update[upd_index][0]--;
        } else {
            nodes[node].update[upd_index][0]++;
        }
        return;
    }
    if (target_start <= (beg + end) / 2) {
        Update(node * 2 + 1, beg, (beg + end) / 2, target_start, target_end, upd_index, upd_value);
    }
    if (target_end > (beg + end) / 2) {
        Update(node * 2 + 2, (beg + end) / 2 + 1, end, target_start, target_end, upd_index, upd_value);
    }
    RefreshNode(node, upd_index);
}

// Sets the wall segment to the condition where there are val options smaller than the current height.
void SetValue(int node, int beg, int end, long long wall_segment, int val) {
    if (beg == end) {
        if (node >= nodes.size())nodes.resize(node + 1);
        nodes[node].sum[0] = (wall_segment + 1) * (2 - val) * powers_of_2[wall_segment] % mod;
        nodes[node].sum[1] = (-wall_segment) * (2 - val) * powers_of_2[n - wall_segment - 1] % mod;
        return;
    }
    if (wall_segment <= (beg + end) / 2) {
        SetValue(node * 2 + 1, beg, (beg + end) / 2, wall_segment, val);
    } else {
        SetValue(node * 2 + 2, (beg + end) / 2 + 1, end, wall_segment, val);
    }
    RefreshNode(node, 0);
    RefreshNode(node, 1);
}

int main() {
    cin >> n;
    long long pw = 1;
    for (int i = 0; i <= n; ++i) {
        powers_of_2.push_back(pw);
        pw = (pw * 2) % mod;
    }
    values = vector<int>(n, 0);

    // Pairs of segment height and index. They'll be sorted by height.
    vector<pair<int, int>> sorted_segments;

    long long answer = 0;
    for (int i = 0; i < 2 * n; ++i) {
        int height;
        cin >> height;
        int index = i;
        if (index >= n)index -= n;
        sorted_segments.push_back({height, index});
        answer = (answer - powers_of_2[n - 1] * height) % mod;
    }
    sort(sorted_segments.begin(), sorted_segments.end());

    // We initialize the segment tree to height 0 by doing update queries. We could do it in a single O(n) operation but this still comfortably fits inside time limits so it doesn't matter.

    for (int i = 0; i < n; ++i) {
        SetValue(0, 0, n - 1, i, 0);
    }
    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            Update(0, 0, n - 1, 0, i - 1, 0, 0);
        }
        if (i + 1 < n) {
            Update(0, 0, n - 1, i + 1, n - 1, 1, 0);
        }
    }

    long long prev_height = 0;
    for (auto[height, index] : sorted_segments) {
        long long cur_sum = nodes[0].GetValue(0) + nodes[0].GetValue(1);
        answer = (answer + cur_sum * (height - prev_height)) % mod;
        prev_height = height;;
        int &val = values[index];
        val++;
        SetValue(0, 0, n - 1, index, val);
        if (index > 0) {
            Update(0, 0, n - 1, 0, index - 1, 0, val);
        }
        if (index + 1 < n) {
            Update(0, 0, n - 1, index + 1, n - 1, 1, val);
        }

    }
    cout << (answer + mod) % mod << endl;

    return 0;
}
