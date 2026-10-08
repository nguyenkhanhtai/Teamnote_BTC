// Mateusz Kussowski
// time complexity: O(n), memory complexity: O(n)
// Solution proposed by the author of the task (with big constant), but with a fairly efficient implementation

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long ll;

const ll MIN_H_CONSTRAINTS = 0;
const ll MAX_H_CONSTRAINTS = 1'000'000'000;
const ll inf = 1000000000000000000;

//returns candidate heights for a[i]
const int max_dif = 9;
const bool include_equals = true;
vector<ll> get_candidate_heights(const vector<ll> &a, int idx)
{
    vector<ll> candidates = {a[idx]};
    for (int i = max(0, idx - max_dif); i <= min((int)a.size() - 1, idx + max_dif); ++i)
    {
        if (i == idx)
            continue;

        candidates.push_back(max(MIN_H_CONSTRAINTS, a[i] - 1));
        candidates.push_back(min(MAX_H_CONSTRAINTS, a[i] + 1));
        if (include_equals)
            candidates.push_back(a[i]);
    }

    // Remove duplicates efficiently
    sort(candidates.begin(), candidates.end());
    candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());

    return candidates;
}

void calculate_dp(vector<vector<pair<ll, ll>>>& last_dp, vector<vector<pair<ll, ll>>>& current_dp, vector<ll>& candidates, ll height, bool allow_equal){
    
    auto last_rpt = last_dp[1].rbegin();
    auto current_rpt = candidates.rbegin();
    ll best_val = inf;
    while(current_rpt != candidates.rend()){
        while(last_rpt != last_dp[1].rend() && last_rpt->first > *current_rpt){
            best_val = min(best_val, last_rpt->second);
            ++last_rpt;
        }

        current_dp[0].push_back({*current_rpt, best_val + abs(*current_rpt - height)});
        
        ++current_rpt;
    }

    reverse(current_dp[0].begin(), current_dp[0].end());

    auto last_pt = last_dp[0].begin();
    auto current_pt = candidates.begin();
    best_val = inf;
    while(current_pt != candidates.end()){
        while(last_pt != last_dp[0].end() && last_pt->first < *current_pt){
            best_val = min(best_val, last_pt->second);
            ++last_pt;
        }

        current_dp[1].push_back({*current_pt, best_val + abs(*current_pt - height)});

        ++current_pt;
    }

    if(allow_equal){
        auto last_it = last_dp[0].begin();
        auto current_it = current_dp[0].begin();
        while(last_it != last_dp[0].end()){
            while(current_it != current_dp[0].end() && current_it->first < last_it->first){
                ++current_it;
            }
            if(current_it == current_dp[0].end()) break;
            if(current_it->first == last_it->first){
                current_it->second = min(current_it->second, last_it->second + abs(current_it->first - height));
            }

            ++last_it;
        }

        last_it = last_dp[1].begin();
        current_it = current_dp[1].begin();
        while(last_it != last_dp[1].end()){
            while(current_it != current_dp[1].end() && current_it->first < last_it->first){
                ++current_it;
            }
            if(current_it == current_dp[1].end()) break;
            if(current_it->first == last_it->first){
                current_it->second = min(current_it->second, last_it->second + abs(current_it->first - height));
            }

            ++last_it;
        }
    }
}

ll solve(const vector<ll>& a){
    if(a.size() <= 2){
        return 0;
    }

    vector<vector<vector<pair<ll, ll>>>> dp(a.size(), vector<vector<pair<ll, ll>>>(2, vector<pair<ll, ll>>()));

    vector<ll> candidate_heights = get_candidate_heights(a, 0);
    for(auto x : candidate_heights){
        dp[0][0].push_back({x, abs(x - a[0])});
        dp[0][1].push_back({x, abs(x - a[0])});
    }

    //special handling for i = 1, because we can't have a[0] == a[1]
    candidate_heights = get_candidate_heights(a, 1);
    calculate_dp(dp[0], dp[1], candidate_heights, a[1], true);
    
    //handle i = 2 ... a.size() - 2
    for(int i = 2; i < (int)a.size() - 1; ++i){
        candidate_heights = get_candidate_heights(a, i);
        calculate_dp(dp[i-1], dp[i], candidate_heights, a[i], true);
    }

    //handle i = a.size() - 1, similar to i = 1
    candidate_heights = get_candidate_heights(a, (int)a.size()-1);
    calculate_dp(dp[a.size()-2], dp[a.size()-1], candidate_heights, a[a.size()-1], true);

    ll best_score = inf;
    for(int i = 0; i < 2; ++i){
        for(auto x : dp[a.size()-1][i]){
            best_score = min(best_score, x.second);
        }
    }
    
    return best_score;
}

void read_input(int& n, vector<ll>& a){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;
    a.resize(n);
    for(int i = 0; i < n; ++i){
        cin >> a[i];
    }
}

int main(){
    int n;
    vector<ll> a;

    read_input(n, a);
    cout << solve(a) << endl;
    
    return 0;
}